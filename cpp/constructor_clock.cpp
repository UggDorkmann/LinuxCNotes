#include<iostream>
#include<cstring>
#include<cstdlib>
#include "../all.h"
using namespace std;
class Clock{
	public:
	Clock(time_t t){
		tm* p = localtime(&t);
		sshour = p->tm_hour;
		ssmin = p->tm_min;
		sssec = p->tm_sec;
	}
	void run(){
		while(1){
			printf("\r%02d:%02d:%02d",sshour,ssmin,sssec);
			fflush(stdout);
			if(sssec>=59){
				sssec = -1;
				ssmin++;
			}
			if(ssmin >= 60){
				ssmin = 0;
				sshour++;
			}
			if(sshour>=24)sshour = 0;
			sssec++;
			sleep(1);
		}
	}
	private:
	int sshour;
	int sssec;
	int ssmin;
};
int main(){
	Clock c(time(0));
	cout << getpid() << endl;
	c.run();
	return 0;
}
