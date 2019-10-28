#include <iostream>
#include <vector>
#include <stdio.h>
//#include "std_lab_facilities.h"

class bucket{
	private:
		int cook;
		int max_size;
	public:
		bucket()
		{
			this->cook = 0;
			this->max_size = 10;
		}
		bool add_cook(int hm)
		{	
			if ((cook + hm) > max_size) return false;

			cook += hm;
			return true;
		}	
		bool delete_cook(int hm)
		{
			if ((cook - hm) < 0) return false;

			cook -= hm;
			return true;
		}
		int get_cook_num()
		{
			return cook;
		}
};

class cookManager{
	private:
		bucket* bucks;
		int buck_size;
		int ite;
	public:
		cookManager()
		{
			this->buck_size = 1;
			this->ite = 0;
			this->bucks = new bucket[buck_size];
		}	
		~cookManager()
		{
			delete[] bucks;
		}
		void realloc_buckets(int demand_size)
                {
                        int new_size = demand_size;
                        if (demand_size < 1) {
                                if (buck_size == 1)
                                        return;
                                else
                                        demand_size = 1;
                        }

                        bucket* new_bucks = new bucket[new_size];

                        int mlimit = ((new_size < buck_size) ? new_size : buck_size);

                        for (int i = 0; i < mlimit; i++) {
                                new_bucks[i] = bucks[i];
                        }

                        delete[] bucks;
                        bucks = new_bucks;

                        buck_size = new_size;
                }

		int total()
		{
			int t = 0;
			for (int i = 0; i <= ite; i++)
				t += bucks[i].get_cook_num();

			return t;
		}

		void add_cookies(int hm)
		{
                	while (bucks[ite].add_cook(hm) == false)
			{
				int blank = 10 - bucks[ite].get_cook_num();
				bucks[ite].add_cook(blank);
				ite++;
				realloc_buckets(buck_size + 1);
				hm -= blank;
			}
		}		
		void delete_cookies(int hm)
		{
			if (total() < hm)
			{
				std::cout << hm-total()<< " out of " << hm << " cookies cannot be eaten." <<std::endl;
				delete_cookies(total());
			}
			else
			{
				while (bucks[ite].delete_cook(hm) == false)
				{
					int remain = bucks[ite].get_cook_num();
					ite--;
					realloc_buckets(buck_size - 1);
					hm -= remain;
				}
			}
		}
		void print_status()
		{
			std::cout << "Bucket Status" <<std::endl;
			std::cout << "-------------" <<std::endl;
			
			if (total() == 0) std::cout << "1st bucket : 0cookies"<<std::endl;
			else
			{
				for (int i = 0; i < ite; i++)
				{
					if (i == 0) std::cout << "1st bucket : ";
					else if (i == 1) std::cout << "2nd bucket : ";
					else if (i == 2) std::cout << "3rd bucket : ";
					else std::cout << i + 1 <<"th bucket : ";

					std::cout << bucks[i].get_cook_num() << "cookies" <<std::endl;
				}

				if (bucks[ite].get_cook_num() != 0) std::cout << ite + 1 <<"th bucket : " <<bucks[ite].get_cook_num() << "cookies" <<std::endl;
			}
			std::cout <<"Keep going? (press 'y' to continue)" <<std::endl;
		}
};

int main() {
	
	char choice = 'y';
	int come_cook, eat_cook;
	cookManager M;

	std::cout << "There is a cookie bucket." <<std::endl;

	while(choice == 'y')
	{
		std::cout << "How many cookies are coming?" <<std::endl;
		std::cin >> come_cook;
		std::cout << "How many cookies are eaten?" <<std::endl;
		std::cin >> eat_cook;
		
		M.add_cookies(come_cook);
		M.delete_cookies(eat_cook);
		M.print_status();
		std::cin >> choice;
	}
}	
