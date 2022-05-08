#include <list>
#include <algorithm>

class PRDS_LRUclean {

   public:

   PRDS_LRUclean(int count) {}

    void push(int x) {
       if (x < 0) num_dirty++;
       q.push_back(x);
    };
    int pop_clean() {
        // Pops the first clean location it finds.
        for (auto iter = q.begin(); iter != q.end(); ++iter){
            if (*iter > 0) {
                int x = *iter;
                q.erase(iter);
                return(x);
            }
        }
    };
    int pop_dirty() {
        // Pops the front of the queue
        int x = q.front();
        if (x < 0) num_dirty--;
        q.pop_front();
        return(x);
    }
    int size() {
        return q.size();
    };

    // When x is referenced, move it to the back of the queue.
    void move_to_back(int nextpage) {
        int i;
        // Find nextpage in q.
        for (auto iter = q.begin(); iter != q.end(); ++iter) {
            if (abs(*iter) == nextpage) {
                // When we find nextpage,
                q.erase(iter);
                push(*iter);
                return;
            }
        }
    }

    list<int> q;
    int num_dirty = 0;

};

int Page_Replacement_LRUclean(vector<int>& pages, int nextpage, PRDS_LRUclean *p)
{
    // TODO: PAGE REPLACEMENT ALGO BELOW IS FOR FIFO, CHANGE TO LRU
    bool found = false;
    int i;
    nextpage = abs(nextpage);

    // Check if nextpage is in the pages array, if so record in LRU list and return -1
    for (i = 0; i < pages.size(); i++) {
        if (abs(pages[i]) == nextpage) {
            found = true;
            p->move_to_back(nextpage);
            return -1;
        }
    }

    if (not found) {
        // Check if there is an empty slot, if so return index for that slot
        for (i = 0; i < pages.size(); i++) {
            if (pages[i] == 0) {
                pages[i] = nextpage;
                p->push(nextpage);
                return i;
            }
        }
        // Get the page to be replaced, and find where it is stored in the pages vector
        int to_replace;
        if (p->num_dirty == pages.size()) {
            to_replace = p->pop_dirty();
        }
        else {
            to_replace = p->pop_clean();
        }
        for (i = 0; i < pages.size(); i++) {
            if (abs(pages[i]) == to_replace)
                break;
        }

        // update the queue for the new page
        p->push(nextpage);
    }

    return i;
}
