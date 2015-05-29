#include "cache.h"
#include <stdlib.h>

using namespace std;


int time_stamp=0;
map<string,GD1_cache_data> GD1_cache;
int mc_GD1 = 0;
int cache_oc_GD1=0;
int average=0;
int mcb_GD1 = 0;
int miss_byte_count=0;
int C_SIZE=0;

string fetch_data_GD1(string URL)
{
	if(GD1_cache.find(URL)!=GD1_cache.end())
		{
			//cout<<"found in GD1"<<endl;
			GD1_cache.find(URL)->second.current_cost = GD1_cache.find(URL)->second.initial_cost;
			return (GD1_cache.find(URL))->second.data;
		}
	else
		return "empty";
}


void update_cache_GD1(string URL,string data, int d_len)
{
	if(d_len>C_SIZE)
		return;
	if((cache_oc_GD1+d_len)<=C_SIZE)
		{
			//cout<<"updating GD1"<<endl;
			GD1_cache.insert(pair<string,GD1_cache_data>(URL,GD1_cache_data(data,time_stamp,d_len)));
			cache_oc_GD1=cache_oc_GD1+d_len;
		}
	else
		{
			//cout<<"throwing away from GD1"<<endl;
			map<string,GD1_cache_data> :: iterator it = GD1_cache.begin();
			string URL_min;
			float cost_min = it->second.current_cost;
			while(it != GD1_cache.end())
			{
				if((it->second).current_cost<=cost_min)
					{
						cost_min = it->second.current_cost;
						URL_min = it->first;
					}
				it++;
			}
			cache_oc_GD1=cache_oc_GD1-GD1_cache.find(URL_min)->second.d_len;
			it = GD1_cache.begin();
			while(it!=GD1_cache.end())
			{
				it->second.current_cost = it->second.current_cost-cost_min;
				it++;
			}
			GD1_cache.erase(URL_min);
			update_cache_GD1(URL,data,d_len);
			
		}
}



map<string,GDF_cache_data> GDF_cache;
multimap<float,string > GDF_p_queue;
float p_que_time=0;
int mc_GDF = 0;
int cache_oc_GDF=0;
int mcb_GDF = 0;

string fetch_data_GDF(string URL)
{
	
	pair <multimap<float,string>::iterator, multimap<float,string>::iterator> ret;
	
	if(GDF_cache.find(URL)!=GDF_cache.end())
		{
			//cout<<"found in GDF"<<endl;
			ret = GDF_p_queue.equal_range(GDF_cache.find(URL)->second.pr);
			multimap<float,string> :: iterator it = ret.first;
			while(it !=ret.second )
			{	
				if((it->second).compare(URL)==0)
				{
					GDF_p_queue.erase(it);
					GDF_cache.find(URL)->second.freq++;
					float pr=p_que_time+((GDF_cache.find(URL)->second.freq)*(GDF_cache.find(URL)->second.cbys));
					GDF_p_queue.insert(pair<float,string>(pr,URL));
					break;
				}
				it ++;
			}
			return (GDF_cache.find(URL))->second.data;
		}
	else
		return "empty";
}


void update_cache_GDF(string URL,string data, int d_len)
{
	if(d_len>C_SIZE)
		return;
	float pr=p_que_time+(1*GDF_cache.find(URL)->second.cbys);
	GDF_cache.insert(pair<string,GDF_cache_data>(URL,GDF_cache_data(data,time_stamp,d_len)));
	GDF_p_queue.insert(pair<float,string>(pr,URL));
	GDF_cache.find(URL)->second.pr=pr;
	cache_oc_GDF=cache_oc_GDF+d_len;
	if(cache_oc_GDF<=C_SIZE)
		{
			return;
		}
	else
		{
			//Case 1 
			multimap<float,string> :: iterator it = GDF_p_queue.begin();
			multimap<float,string> :: iterator it1 = GDF_p_queue.begin();
			int sum=0;
			int nac=0;
			while(it!=GDF_p_queue.end() && sum<d_len)
			{
				if(it->second.compare(URL)!=0)
					sum=sum+GDF_cache.find(it->second)->second.d_len;
				else
					{
						nac=1;
						break;
					}
				it++;
			}
			if(nac)
				{
					cache_oc_GDF = cache_oc_GDF-d_len;
					GDF_cache.erase(URL);
					GDF_p_queue.erase(it);
					return;
				}
			else
				{
					it++;
					//cout<<"updating GDF "<<endl;
					while(it1!=it)
					{
						if(it1==GDF_p_queue.end())
							break;
						//cout<<"throwing away from GDF"<<it1->second<<endl;
						cache_oc_GDF=cache_oc_GDF-GDF_cache.find(it1->second)->second.d_len;
						GDF_cache.erase(it1->second);
						p_que_time=it1->first;
						GDF_p_queue.erase(it1++);
					}
				return;
				}

			
		}
}



map<string,lfu_cache_data> lfu_cache;
multimap<int,string> lfu_status;
int mc_lfu = 0;
int cache_oc_lfu=0;
int mcb_lfu = 0;
string fetch_data_lfu(string URL)
{
	pair <multimap<int,string>::iterator, multimap<int,string>::iterator> ret;
	if(lfu_cache.find(URL)!=lfu_cache.end())
		{
			//cout<<"found in lfu"<<endl;
			ret = lfu_status.equal_range(lfu_cache.find(URL)->second.timestamp);
			multimap<int,string>::iterator it = ret.first;
			
			while(it!=ret.second)
			{
				if((it->second).compare(URL)==0)
				{
					lfu_status.erase(it);
					break;
				}
				else
					it++;
			}
			lfu_cache.find(URL)->second.timestamp=lfu_cache.find(URL)->second.timestamp++;
			lfu_status.insert(pair<int,string>(lfu_cache.find(URL)->second.timestamp,URL));
			return (lfu_cache.find(URL))->second.data;
		}
	else
		return "empty";
}


void update_cache_lfu(string URL,string data, int d_len)
{
	if(d_len>C_SIZE)
		return;
	if((cache_oc_lfu+d_len)<=C_SIZE)
		{
			//cout<<"updating cache lfu"<<endl;
			lfu_cache.insert(pair<string,lfu_cache_data>(URL,lfu_cache_data(data,0,d_len)));
			lfu_status.insert(pair<int,string>(0,URL));
			cache_oc_lfu=cache_oc_lfu+d_len;
			
		}
	else
		{
			//cout<<"throwing away from lfu";
			//cout<<lfu_status.begin()->second<<endl;
			cache_oc_lfu=cache_oc_lfu-lfu_cache.find(lfu_status.begin()->second)->second.d_len;
			lfu_cache.erase(lfu_status.begin()->second);
			lfu_status.erase(lfu_status.begin());
			update_cache_lfu(URL,data,d_len);
			
		}
}


map<string,lru_cache_data> lru_cache;
map<int,string> lru_status;
int mc_lru = 0;
int cache_oc_lru=0;
int mcb_lru = 0;

string fetch_data_lru(string URL)
{
	if(lru_cache.find(URL)!=lru_cache.end())
		{
			//cout<<"found in lru"<<endl;
			lru_status.erase(lru_cache.find(URL)->second.timestamp);
			lru_cache.find(URL)->second.timestamp=time_stamp;
			lru_status.insert(pair<int,string>(time_stamp,URL));
			return (lru_cache.find(URL))->second.data;
		}
	else
		return "empty";
}


void update_cache_lru(string URL,string data, int d_len)
{
	if(d_len>C_SIZE)
		return;
	if((cache_oc_lru+d_len)<=C_SIZE)
		{
			//cout<<"updating lru"<<endl;
			lru_cache.insert(pair<string,lru_cache_data>(URL,lru_cache_data(data,time_stamp,d_len)));
			lru_status.insert(pair<int,string>(time_stamp,URL));
			cache_oc_lru=cache_oc_lru+d_len;
			
		}
	else
		{
			//cout<<"throwing away from lru "<<endl;
			map<int,string> :: iterator it = lru_status.begin();
			//cout<<it->second<<endl;
			cache_oc_lru=cache_oc_lru-lru_cache.find(it->second)->second.d_len;
			lru_cache.erase(it->second);
			lru_status.erase(it->first);
			update_cache_lru(URL,data,d_len);
			
		}
}



map<string,MAXS_cache_data> MAXS_cache;
multimap<int,string, greater<int>> MAXS_status;
int mc_MAXS = 0;
int cache_oc_MAXS=0;
int mcb_MAXS = 0;
string fetch_data_MAXS(string URL)
{
	if(MAXS_cache.find(URL)!=MAXS_cache.end())
		{
			//cout<<"found in MAXS"<<endl;
			return (MAXS_cache.find(URL))->second.data;
		}
	else
		return "empty";
}


void update_cache_MAXS(string URL,string data, int d_len)
{
	if(d_len>C_SIZE)
		return;
	if((cache_oc_MAXS+d_len)<=C_SIZE)
		{
			//cout<<"updating cache MAXS"<<endl;
			MAXS_cache.insert(pair<string,MAXS_cache_data>(URL,MAXS_cache_data(data,time_stamp,d_len)));
			MAXS_status.insert(pair<int,string>(d_len,URL));
			cache_oc_MAXS=cache_oc_MAXS+d_len;
			
		}
	else
		{
			//cout<<"throwing away from MAXS "<<endl;
			//cout<<MAXS_status.begin()->second<<endl;
			cache_oc_MAXS=cache_oc_MAXS-MAXS_cache.find(MAXS_status.begin()->second)->second.d_len;
			MAXS_cache.erase(MAXS_status.begin()->second);
			MAXS_status.erase(MAXS_status.begin());
			update_cache_MAXS(URL,data,d_len);
			
		}
}


map<string,random_cache_data> random_cache;
map<int,string, greater<int> > random_status;
int mc_random = 0;
int cache_oc_random=0;
int mcb_random = 0;
string fetch_data_random(string URL)
{

	if(random_cache.find(URL)!=random_cache.end())
		{
			//cout<<"found in random cache"<<endl;
			random_status.erase(random_cache.find(URL)->second.timestamp);
			random_cache.find(URL)->second.timestamp=time_stamp;
			random_status.insert(pair<int,string>(time_stamp,URL));
			return (random_cache.find(URL))->second.data;
		}
	else
		return "empty";
}


void update_cache_random(string URL,string data, int d_len)
{
	if(d_len>C_SIZE)
		return;
	if((cache_oc_random+d_len)<=C_SIZE)
		{
			//cout<<"updating cache random"<<endl;
			random_cache.insert(pair<string,random_cache_data>(URL,random_cache_data(data,time_stamp,d_len)));
			random_status.insert(pair<int,string>(time_stamp,URL));
			cache_oc_random=cache_oc_random+d_len;
			
		}
	else
		{
			//cout<<"throwing away from random"<<endl;;
			int count =0;
			map<int,string> :: iterator it = random_status.begin();
			int rand_number=rand()%random_status.size();
			while(count<rand_number)
				{it++ ;
				 count++;
				 }
			//cout<<it->second<<endl;
			cache_oc_random=cache_oc_random-random_cache.find(it->second)->second.d_len;
			random_cache.erase(it->second);
			random_status.erase(it->first);
			update_cache_random(URL,data,d_len);
			
		}
}



map<string,lru_min_cache_data> lru_min_cache;
multimap<int,string, greater<int> > lru_min_status;
map<int,string>lru_min_tem;
int mc_lru_min = 0;
int cache_oc_lru_min=0;
int mcb_lru_min = 0;

string fetch_data_lru_min(string URL)
{
	if(lru_min_cache.find(URL)!=lru_min_cache.end())
		{
			//cout<<"found in lru_min"<<endl;
			lru_min_cache.find(URL)->second.timestamp=time_stamp;
			return (lru_min_cache.find(URL))->second.data;
		}
	else
		return "empty";
}

void update_cache_lru_min(string URL,string data, int d_len)
{
	if(d_len>C_SIZE)
		return;
	if((cache_oc_lru_min+d_len)<=C_SIZE)
		{
			//cout<<"updating cache lru_min"<<endl;
			lru_min_cache.insert(pair<string,lru_min_cache_data>(URL,lru_min_cache_data(data,time_stamp,d_len)));
			lru_min_status.insert(pair<int,string>(d_len,URL));
			cache_oc_lru_min=cache_oc_lru_min+d_len;
			
		}
	else
		{
		int temp_size=0;
		//cout<<"throwing away from lru_min ";
		while(true)
			{
				multimap<int,string> :: iterator it = lru_min_status.begin();
				//cout<<it->second<<endl;
				while((it!=lru_min_status.end()) && (lru_min_cache.find(it->second)->second.d_len >=d_len))
				{
					lru_min_tem.insert(pair<int,string>(lru_min_cache.find(it->second)->second.timestamp,it->second));
					it++;
				}
				pair <multimap<int,string>::iterator, multimap<int,string>::iterator> ret;
				while(lru_min_tem.size() && temp_size<d_len )
				{
					map<int,string> :: iterator it1 = lru_min_tem.begin();
					temp_size = temp_size+lru_min_cache.find(it1->second)->second.d_len;
					cache_oc_lru_min=cache_oc_lru_min-lru_min_cache.find(it1->second)->second.d_len;
					ret=lru_min_status.equal_range(lru_min_cache.find(it1->second)->second.d_len);
					lru_min_status.erase(ret.first);
					lru_min_cache.erase(it1->second);
					lru_min_tem.erase(it1);
				}
				if(cache_oc_lru_min+d_len<=C_SIZE)
				{
					lru_min_tem.clear();
					break;
				}
				else
				{
					d_len=d_len/2;
					lru_min_tem.clear();
				}
		}
		//cout<<"updating cache"<<endl;
		lru_min_cache.insert(pair<string,lru_min_cache_data>(URL,lru_min_cache_data(data,time_stamp,d_len)));
		lru_min_status.insert(pair<int,string>(d_len,URL));
		cache_oc_lru_min=cache_oc_lru_min+d_len;
		}
}



map<string,fifo_cache_data> fifo_cache;
queue<string> fifo_status;
int mc_fifo = 0;
int cache_oc_fifo=0;
int mcb_fifo = 0;
string fetch_data_fifo(string URL)
{
	if(fifo_cache.find(URL)!=fifo_cache.end())
		{
			return (fifo_cache.find(URL))->second.data;
		}
	else
		return "empty";
}


void update_cache_fifo(string URL,string data, int d_len)
{
	if(d_len>C_SIZE)
		return;
	if((cache_oc_fifo+d_len)<=C_SIZE)
		{

			fifo_cache.insert(pair<string,fifo_cache_data>(URL,fifo_cache_data(data,d_len)));
			fifo_status.push(URL);
			cache_oc_fifo=cache_oc_fifo+d_len;
			
		}
	else
		{
			
			//cout<<fifo_status.front()<<endl;
			cache_oc_fifo=cache_oc_fifo-(fifo_cache.find(fifo_status.front())->second.d_len);
			fifo_cache.erase(fifo_status.front());
			fifo_status.pop();
			update_cache_fifo(URL,data,d_len);
			
		}
}

vector<int> URL_l_list;
float calculate(int accesses)
{
	vector<int> :: iterator it = URL_l_list.begin();
	int sum=0;
	while(it!=URL_l_list.end())
		{
			sum=sum+(*it);
			it++;
		}
	average = sum/accesses;
	return average;
}

int num_small_pages()
{
	vector<int> :: iterator it = URL_l_list.begin();
	int count=0;
	while(it!=URL_l_list.end())
		{	
			if(average>*it)
				count++;
			it++;
		}
	average=0;
	URL_l_list.clear();
	return count;
	
}

float calc_hit_ratio(int misses,int accesses)
{
	return (1.0-((float)misses/float(accesses)));
}

float calc_byte_hit_ratio(int hit_length, int total)
{
	return (float)hit_length/float(total);
}

void clear_everything()
  {
 	
	GD1_cache.clear();
	mc_GD1=0;
	mcb_GD1=0;
	cache_oc_GD1=0;

	MAXS_cache.clear();
	MAXS_status.clear();
	mc_MAXS=0;
	mcb_MAXS=0;
	cache_oc_MAXS=0;

	fifo_cache.clear();
	while(fifo_status.size())
	{
		fifo_status.pop();
	}
	mc_fifo=0;
	mcb_fifo=0;
	cache_oc_fifo=0;

	lru_min_cache.clear();
	lru_min_status.clear();
	lru_min_tem.clear();
	mc_lru_min=0;
	mcb_lru_min=0;
	cache_oc_lru_min=0;
	
	lru_cache.clear();
	lru_status.clear();
	mc_lru=0;
	mcb_lru=0;
	cache_oc_lru=0;


	lfu_cache.clear();
	lfu_status.clear();
	mc_lfu=0;
	mcb_lfu=0;
	cache_oc_lfu=0;

	GDF_cache.clear();
	GDF_p_queue.clear();
	p_que_time=0;
	mc_GDF=0;
	mcb_GDF=0;
	cache_oc_GDF=0;

	random_cache.clear();
	random_status.clear();
	mc_random=0;
	mcb_random=0;
	cache_oc_random=0;


	time_stamp=0;
  }

