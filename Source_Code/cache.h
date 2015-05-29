#include <iostream>
#include <string.h>
#include <map>
#include <queue>


using namespace std ;


extern int time_stamp;
extern int C_SIZE;
class GD1_cache_data
{
	public:
		int timestamp;
		string data;
		int d_len;
		float initial_cost;
		float current_cost;
		GD1_cache_data(string d, int ts, int d_l):timestamp(ts), data(d), d_len(d_l)
		{
			initial_cost = 1/d_len;
			current_cost = 1/d_len;
		}
};


extern map<string,GD1_cache_data> GD1_cache;
string fetch_data_GD1(string URL);
void update_cache_GD1(string URL, string data, int d_len);
extern int mc_GD1;
extern int cache_oc_GD1;
extern int mcb_GD1;

class GDF_cache_data
{
	public:
		int timestamp;
		string data;
		int d_len;
		int freq;
		float cbys ;
		float pr;
		GDF_cache_data(string d, int ts, int d_l):timestamp(ts), data(d), d_len(d_l)
		{
			freq=1;
			cbys = ((float)2+((float)d_l/(float)536))/d_l;
		
		}
};

extern map<string,GDF_cache_data> GDF_cache;
extern multimap<float,string> GDF_p_queue;
extern float p_que_time;
string fetch_data_GDF(string URL);
void update_cache_GDF(string URL, string data, int d_len);
extern int mc_GDF;
extern int cache_oc_GDF;
extern int mcb_GDF;

class lfu_cache_data
{
	public:
		int timestamp;
		string data;
		int d_len;
		lfu_cache_data(string d, int ts, int d_l):timestamp(0), data(d), d_len(d_l)
		{}
};



extern map<string,lfu_cache_data> lfu_cache;
extern multimap<int,string> lfu_status;
string fetch_data_lfu(string URL);
void update_cache_lfu(string URL, string data, int d_len);
extern int mc_lfu;
extern int cache_oc_lfu;
extern int mcb_lfu;

class lru_cache_data
{
	public:
		int timestamp;
		string data;
		int d_len;
		lru_cache_data(string d, int ts, int d_l):timestamp(ts), data(d), d_len(d_l)
		{}
};


extern map<string,lru_cache_data> lru_cache;
extern map<int,string> lru_status;
string fetch_data_lru(string URL);
void update_cache_lru(string URL, string data, int d_len);
extern int mc_lru;
extern int cache_oc_lru;
extern int mcb_lru;

class lru_min_cache_data
{
	public:
		int timestamp;
		string data;
		int d_len;
		lru_min_cache_data(string d, int ts, int d_l):timestamp(ts), data(d), d_len(d_l)
		{}
};


extern map<string,lru_min_cache_data> lru_min_cache;
extern multimap<int,string, greater<int> > lru_min_status;
extern map<int,string>lru_min_tem;
string fetch_data_lru_min(string URL);
void update_cache_lru_min(string URL, string data, int d_len);
extern int mc_lru_min;
extern int cache_oc_lru_min;
extern int mcb_lru_min;

class MAXS_cache_data
{
	public:
		int timestamp;
		string data;
		int d_len;
		MAXS_cache_data(string d, int ts, int d_l):timestamp(ts), data(d), d_len(d_l)
		{}
};


extern map<string,MAXS_cache_data> MAXS_cache;
extern multimap<int,string, greater<int> > MAXS_status;
string fetch_data_MAXS(string URL);
void update_cache_MAXS(string URL, string data, int d_len);
extern int mc_MAXS;
extern int cache_oc_MAXS;
extern int mcb_MAXS;

class random_cache_data
{
	public:
		int timestamp;
		string data;
		int d_len;
		random_cache_data(string d, int ts, int d_l):timestamp(ts), data(d), d_len(d_l)
		{}
};


extern map<string,random_cache_data> random_cache;
extern map<int,string, greater<int> > random_status;
string fetch_data_random(string URL);
void update_cache_random(string URL, string data, int d_len);
extern int mc_random;
extern int cache_oc_random;
extern int mcb_random;

class fifo_cache_data
{
	public:
		string data;
		int d_len;
		fifo_cache_data(string d, int d_l):data(d), d_len(d_l)
		{}
};


extern map<string,fifo_cache_data> fifo_cache;
extern queue<string> fifo_status;
extern int mc_fifo;
string fetch_data_fifo(string URL);
void update_cache_fifo(string URL, string data, int d_len);
extern int cache_oc_fifo;
extern int mcb_fifo;


extern vector<int> URL_l_list;
float calculate(int accesses);
int num_small_pages();
extern int average;
float calc_hit_ratio(int misses,int accesses);
float calc_byte_hit_ratio(int hit_length, int total);
void clear_everything();
