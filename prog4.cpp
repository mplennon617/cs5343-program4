#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;
//
//	Uncomment the following lines to test your program
#include "prog4_MRU.h"
#include "prog4_LRUclean.h"
#include "prog4_MyOwn.h"



class PRDS_FIFO {
   public:
	PRDS_FIFO (int x) {};  // x denotes the number of size of the page vector (max # of pages in main memory)

	void push(int x) {q.push_back(x);};
	int pop() {int x = q.front(); q.pop_front(); return(x);};
        int size() {return q.size();};

	deque<int> q;

};


/*

	Page Replacement algorithm:

	Parameter:	
		pages: a vector storing the set of pages that is curently in memory
		nextpage: the next page to be accesses
		p : a pointer to the data structure that is used for the page replacement

	Output:
		-1 : if no page replacement is needed
		any other number: the index in the pages vector that is to be replaced

*/

int Page_Replacement_FIFO(vector<int>& pages, int nextpage, PRDS_FIFO* p)
{
   bool found = false;
   int i;
   nextpage = abs(nextpage);

   /*
      Check if nextpage is in the pages array, if so return -1
   */
   for (i = 0; i < pages.size(); i++)
	{
	   if (abs(pages[i]) == nextpage)
		{
		   found = true;
		   return -1;
		}
	}

   if (not found)
	{
	   /*
	      Check if there is an empty slot, if so return index for that slot
	   */
	   for (i = 0; i < pages.size(); i++)
	 	if (pages[i] == 0)
			{
			   pages[i] = nextpage;
			   p->push(nextpage);
			   return i; 
			}
	   /*
	      Get the page to be replace, and find where it is stored in the pages vector
	   */
	   int to_replace = p->pop(); 
	   for (i = 0; i < pages.size(); i++)
		{
		   if (abs(pages[i]) == to_replace)
			break;
		}

	   /*
  	       update the queue for the new page
	   */

	   p->push(nextpage);
	}

   return i;
}

void test_case(string fname, int count)
{
   vector<int> pagelist;

   vector<int> pages_FIFO;
   PRDS_FIFO *prds = new PRDS_FIFO(count);
   vector<int> pages_LRUclean;
   PRDS_LRUclean *prds_LRUclean = new PRDS_LRUclean(count);
   vector<int> pages_MRU;
   PRDS_MRU *prds_MRU = new PRDS_MRU(count);
   vector<int> pages_MyOwn;
   PRDS_MyOwn *prds_MyOwn = new PRDS_MyOwn(count);

   int replace_count_FIFO = 0;
   int replace_count_LRUclean = 0;
   int replace_count_MRU = 0;
   int replace_count_MyOwn = 0;

   int write_count_FIFO = 0;
   int write_count_LRUclean = 0;
   int write_count_MRU = 0;
   int write_count_MyOwn = 0;


   /*
    	initialize the buffer to be empty (0)
   */
   for (int i = 0; i < count; i++)
	{
	pages_FIFO.push_back(0);
    pages_LRUclean.push_back(0);
    pages_MRU.push_back(0);
	/*
     		Uncomment the appropriate line(s) to test your program
	pages_MyOwn.push_back(0);
	*/
	}

   ifstream ifile;
   ifile.open(fname);
   int n;
   ifile >> n;
   
   for (int i = 0; i < n; i++)
	{
	  int x;
	  ifile >> x;
	  pagelist.push_back(x);
	}

   //	Code for FIFO

   for (int i = 0; i < n; i++)
	{

	   int res = Page_Replacement_FIFO(pages_FIFO, pagelist[i], prds);

  	   if (res >  1)
		{
		   replace_count_FIFO++;
		   if (pagelist[i] < 0)
			write_count_FIFO++;
		   pages_FIFO[res] = pagelist[i];
		}
	   else if (pagelist[i] < 0)
		   {
			for (int j = 0; j < pages_FIFO.size(); j++)
			{
				if (pages_FIFO[j] == -pagelist[i])
					pages_FIFO[j] = -pages_FIFO[j];
			}
			
		   }

	   cout << "FIFO " << fname << " " << count << " | " << pagelist[i] << "  " << res << "  :  ";
	   for (int i = 0; i < pages_FIFO.size(); i++)
		cout << pages_FIFO[i] << " ";
	   cout << endl;
	}
   cout << endl << fname << " " << count << "  Page replaced count FIFO : " << replace_count_FIFO << " | Write count FIFO :" << write_count_FIFO << "  | Total : " << replace_count_FIFO + write_count_FIFO << endl;
   cout << endl;


   //	Code for MRU 

   for (int i = 0; i < n; i++)
	{

	   int res = Page_Replacement_MRU(pages_MRU, pagelist[i], prds_MRU);

  	   if (res > -1)
		{
		   replace_count_MRU++;
		   if (pagelist[i] < 0)
			write_count_MRU++;
		   pages_MRU[res] = pagelist[i];
		}
	   else if (pagelist[i] < 0)
		   {
			for (int j = 0; j < pages_MRU.size(); j++)
			{
				if (pages_MRU[j] == -pagelist[i])
					pages_MRU[j] = -pages_MRU[j];
			}
			
		   }

	   cout << "MRU " << fname << " " << count << " | " << pagelist[i] << "  " << res << "  :  ";
	   for (int i = 0; i < pages_MRU.size(); i++)
		cout << pages_MRU[i] << " ";
	   cout << endl;
	}
   cout << endl << fname << " " << count << "  Page replaced count MRU : " << replace_count_MRU << " | Write count MRU :" << write_count_MRU << "  | Total : " << replace_count_MRU + write_count_MRU << endl;
   cout << endl;

   //	Code for LRUclean 

   for (int i = 0; i < n; i++)
	{

	   int res = Page_Replacement_LRUclean(pages_LRUclean, pagelist[i], prds_LRUclean);

  	   if (res > -1)
		{
		   replace_count_LRUclean++;
		   if (pagelist[i] < 0)
			write_count_LRUclean++;
		   pages_LRUclean[res] = pagelist[i];
		}
	   else if (pagelist[i] < 0)
		   {
			for (int j = 0; j < pages_LRUclean.size(); j++)
			{
				if (pages_LRUclean[j] == -pagelist[i])
					pages_LRUclean[j] = -pages_LRUclean[j];
			}
			
		   }

	   cout << "LRUclean " << fname << " " << count << " | " << pagelist[i] << "  " << res << "  :  ";
	   for (int i = 0; i < pages_LRUclean.size(); i++)
		cout << pages_LRUclean[i] << " ";
	   cout << endl;
	}
   cout << endl << fname << " " << count << "  Page replaced count LRUclean : " << replace_count_LRUclean << " | Write count LRUclean :" << write_count_LRUclean << "  | Total : " << replace_count_LRUclean + write_count_LRUclean << endl;
   cout << endl;


   //	Code for MyOwn 

   for (int i = 0; i < n; i++)
	{

	   int res = Page_Replacement_MyOwn(pages_MyOwn, pagelist[i], prds_MyOwn);

  	   if (res > -1)
		{
		   replace_count_MyOwn++;
		   if (pagelist[i] < 0)
			write_count_MyOwn++;
		   pages_MyOwn[res] = pagelist[i];
		}
	   else if (pagelist[i] < 0)
		   {
			for (int j = 0; j < pages_MyOwn.size(); j++)
			{
				if (pages_MyOwn[j] == -pagelist[i])
					pages_MyOwn[j] = -pages_MyOwn[j];
			}
			
		   }

	   cout << "MyOwn " << fname << " " << count << " | " << pagelist[i] << "  " << res << "  :  ";
	   for (int i = 0; i < pages_MyOwn.size(); i++)
		cout << pages_MyOwn[i] << " ";
	   cout << endl;
	}
   cout << endl << fname << " " << count << "  Page replaced count MyOwn : " << replace_count_MyOwn << " | Write count MyOwn :" << write_count_MyOwn << "  | Total : " << replace_count_MyOwn + write_count_MyOwn << endl;
   cout << endl;



}

int main(int argc, char **argv)
{
  test_case(argv[1], 3);
  test_case(argv[1], 5);
  return 0;
/*
  test_case("test1.txt", 3);
  test_case("test1.txt", 5);
  test_case("test2.txt", 3);
  test_case("test2.txt", 6);
  test_case("test3.txt", 4);
  test_case("test3.txt", 6);
  test_case("test4.txt", 3);
  test_case("test4.txt", 5);
  test_case("test5.txt", 4);
  test_case("test5.txt", 6);
  test_case("test6.txt", 3);
  test_case("test6.txt", 5);
  test_case("test7.txt", 3);
  test_case("test7.txt", 5);
  test_case("test8.txt", 3);
  test_case("test8.txt", 5);
  test_case("test9.txt", 2);
  test_case("test9.txt", 5);
  test_case("test10.txt", 3);
  test_case("test10.txt", 5);
*/

}
