#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<time.h>
#include<stdlib.h>
using namespace std;

double money;
int day;
int cnt,idx=0;

typedef struct Pig{ //猪 
	int id;//编号 
	int ty;//种类 
	int growday;//饲养日期 
	double weight;//重量 
	int pen;//在几号猪圈 
	struct Pig *next;
}Pig,*PigList;

struct PigPen{//猪圈 
	int sum;//有多少头猪
	int a,b,c;//小花猪、大白花猪、黑猪的数量 
	bool flag;//是否有黑猪 
	int pigid[11];//每头猪的id 
}pigpen[111];


//查找编号为id的猪 
void find(PigList L,int id){
    Pig *p=L->next;
    int i=0;
    while(p){
    	if(p->id==id) {//找到后输出信息 
    		cout<<"此猪为 ";	
			if(p->ty==1)cout<<"小花猪，";
			if(p->ty==2)cout<<"大白花猪，";
			if(p->ty==3) cout<<"黑猪，";
			cout<<"体重为 "<<p->weight<<"kg,";
			cout<<"饲养时间为 "<<p->growday/30<<"月"<<p->growday%30<<"天";
   		
    		return;
    	}
        p=p->next;
    } 
} 
 
//为新增小猪分配猪圈 
int getpen(int k)
{
	int x=-1;
	//小花猪,大白花猪
	if(k==1||k==2){
		for(int i=0;i<100;i++)
		{
			//从没有黑猪的猪圈里找猪数量最少的圈 
			if(!pigpen[i].flag && (x==-1||pigpen[i].sum<pigpen[x].sum))
				x=i;
		}
		//没有找到无黑猪的或者全都满了 
		if(x==-1||pigpen[x].sum==10)
			return -1; 
	}
	else {//黑猪 
		for(int i=0;i<100;i++)
		{
			//优先放入已经有黑猪并且没有满的猪圈 
			if(pigpen[i].flag && pigpen[i].sum<10)
			{
				return i;
			}	
		}
		//如果没有找到,找个空的分配给它 
		for(int i=0;i<100;i++){
			if(pigpen[i].sum == 0)
				return i;
		}
	}
	
	return x;
}

//加入小猪仔 
PigList PigListInsert(PigList L) {
    Pig *pre;                     
    pre = L;
    while( pre->next!=NULL )  
	  pre = pre->next;     //查找最后一个结点的前驱节点 
	
    Pig *p;    //要插入的结点为p
    p = (Pig *)malloc(sizeof(Pig));
    p->id = ++idx;//编号 
	p->ty = rand()%3+1;//种类1-3代表三种猪 
	p->growday = 0;//初始饲养日期为0 
	p->weight = rand()%50+20; //随机产生重量 
	p->pen = getpen(p->ty); //为小猪分配猪圈 
//	cout<<p->id<<' '<<p->ty<<' '<<p->growday<<' '<<p->weight<<' '<<p->pen<<endl; 
	if(p->pen==-1) {
		cout<<"猪圈已满/猪会打架,无法放入！！！"<<endl; 
		return L;
	}
	else 
	{
		//小猪加入猪圈 
		pigpen[p->pen].pigid[pigpen[p->pen].sum]=idx;
		
		if(p->ty == 1) pigpen[p->pen].a++;
		else if(p->ty == 2) pigpen[p->pen].b++;
		else pigpen[p->pen].c++,pigpen[p->pen].flag=true;
		
		pigpen[p->pen].sum++;//此猪圈内猪的个数增加1 
	}
    p->next = pre->next;
    pre->next = p;
 	
    return L;
}


//链表初始化
PigList PigListInit() {
    Pig *L;
    L = (Pig *)malloc(sizeof(Pig));   //申请结点空间
    if(L==NULL){    //判断申请空间是否失败
    	cout<<"申请空间失败!"<<endl; 
        exit(0);    //如果失败则退出程序
    }
    L->next = NULL;          //将next设置为NULL,初始长度为0的单链表
    return L;
}
 //小猪重量增加k千克 
PigList grow(PigList L,double k) {
    Pig *p=L->next;
    int i=0;
    while(p){
        p->growday ++;
		p->weight = p->weight + k; 
        p=p->next;
    }
    return L;
}

//把编号为k的小猪从猪圈中删除 
void pendel(int x,int k,int t)
{
	int n=pigpen[x].sum;//当前猪圈内猪的数量 
	for(int i=1;i<=n;i++)
	{
		if(pigpen[x].pigid[i]==k)//查找到了 
		{
			for(int j=i;j<=n;j++)//后面的编号都前移一位 
				pigpen[x].pigid[j]=pigpen[x].pigid[j+1];
			break;
		}
	}
	pigpen[x].sum--;//当前猪圈内猪的数量减一 
	if(t==1) pigpen[x].a--;
	if(t==2) pigpen[x].b--;
	if(t==3) pigpen[x].c--;
	if(pigpen[x].c<=0) pigpen[x].flag=0;//没有黑猪了 
} 
 
//删除可以出圈的猪 
PigList del(PigList L) {
   
    double money=0;//本次出圈的猪能卖多少钱 
    int f=1;
    while(f)
	{       
	 	Pig *p,*pre;   //pre为前驱结点，p为查找的结点。
    	p = L;
    	f=0;
	    while(p->next) 
        {
	        pre = p;
	        p = p->next;
	        //符合条件,可以出圈 
	        if(p->weight>150||p->growday>365)
			{
				double x;//单价 
				
				if(p->ty==1) x=7;
				else if(p->ty==2) x=6;
				else x=15;
				
				money+=x*(p->weight);
				
				pendel(p->pen,p->id,p->ty);//从猪圈中删除 
				
				f=1;//找到了一个可以出圈的,如果没找到,f=0,循环停止 
				break;
			}		
		}
		pre->next = p->next;          //删除操作，将其前驱next指向其后继。
  		free(p);
    }
   
    cout<<"本次出圈的猪总售价为："<<money<<endl; 
    return L;
}

//统计第k种猪的数量、体重、饲养时间分布情况
void cla(PigList L,int k)
{
	int s=0;//数量
	double w=0;//体重
	int mint=10000,maxt=0;//时间
	int v[111]={0};//猪圈分布 
	Pig *p=L->next;
	if(p==NULL) {
		cout<<"猪圈中没有此类猪!!!"<<endl; 
		return;
	}
    int i=0;
    while(p){
    	//找到了一个 
    	if(p->ty==k) {
    		s++;//数量加一 
    		w+=p->weight;//总重量增加 
    		v[p->pen]=1;//标记它所在猪圈的编号
    		mint=min(mint,p->growday);//最小的猪 
    		maxt=max(maxt,p->growday);//最大的猪 
    	} 
        p=p->next;
    } 
    if(k==1)cout<<"小花猪";
	if(k==2)cout<<"大白花猪";
	if(k==3) cout<<"黑猪";
	cout<<"的数量为"<<s;
	if(s==0) {
		cout<<endl<<endl;
		return;
	}
	cout<<",总重量为"<<w<<"\n其中最小的猪饲养时间为"<<mint<<"天,最大的猪有"
	<<maxt<<"天\n分布的猪圈有 ";
	for(int i=0;i<100;i++)
		if(v[i]) cout<<i<<' ';
	cout<<endl<<endl; 
}
int main(){
	time_t t;
	srand((unsigned) time(&t));
	
	//创建一个链表并初始化 
    PigList list;
    list = PigListInit();
 	//随机放入cnt头小猪 
	cnt=rand()%10+1;
	//cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)
    PigListInsert(list);
    	
	cout<<"\n\n\n\n\n\n\n";
	cout<<"            ======================================================\n";
	cout<<'\n';
	cout<<"                       请选择操作：\n";
	cout<<'\n';
	cout<<"                            1.下一天\n";		
	cout<<"                            2.查询某猪圈猪的数量和种类\n";
	cout<<"                            3.查询某猪圈某头猪的状态信息\n";
	cout<<"                            4.统计每种猪的数量、体重、饲养时间分布情况\n";
	cout<<"                            5.退出\n";
	cout<<'\n';
	cout<<"            ======================================================\n";

	while(1)
	{				
		int op;
		cin>>op;
		switch(op){
       		case 1:{
       			day++;
       			int x=rand()%12;
			    list = grow(list,0.1*x);	
				if(day%90==0) //三个月了,出圈
				{
					del(list);
					//放入新的小猪 
					cnt=rand()%5+1;
					for(int i=1;i<=cnt;i++)
				     	PigListInsert(list);
					
				}    	  	
				break;
			}
			case 2:{
				int x;
				cout<<"请输入猪圈编号：";
   		      	cin>>x;
   		      	cout<<"此猪圈有"<<pigpen[x].sum<<"头猪，其中有黑猪"<<pigpen[x].c<<"头，小花猪"<<pigpen[x].a<<"头，大白花猪"<<pigpen[x].b<<"头\n\n";

				break;
			}
			case 3:{
				int x;
				cout<<"请输入猪圈编号：";
   		      	cin>>x;
   		      	cout<<"此猪圈有"<<pigpen[x].sum<<"头猪,请输入猪的编号: ";
				
				int y;
				cin>>y;
				while(y<0||y>=pigpen[x].sum)  
				{
					cout<<"编号不合法,请重新输入: ";
					cin>>y;
				}
				//cout<<pigpen[x].pigid[y]<<endl;
				find(list,pigpen[x].pigid[y]);
				break;
			}
			case 4:{
				cla(list,1);
				cla(list,2);
				cla(list,3);
				break;
			} 
			case 5:{
				return 0;
			}
			default:break;
		}
		
	}
	
	return 0;
} 




