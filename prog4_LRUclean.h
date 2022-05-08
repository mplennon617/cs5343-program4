#include <list>
#include <algorithm>

class PRDS_LRUclean {

   public:

   PRDS_LRUclean(int count) {}

   // TODO: DS IMPLEMENTATION BELOW IS FOR FIFO, CHANGE TO LRU
    void push(int x) {q.push_back(x);};
    int pop() {int x = q.front(); q.pop_front(); return(x);};
    int size() {return q.size();};

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
        int to_replace = p->pop();
        for (i = 0; i < pages.size(); i++) {
            if (abs(pages[i]) == to_replace)
                break;
        }

        // update the queue for the new page
        p->push(nextpage);
    }

    return i;
}
