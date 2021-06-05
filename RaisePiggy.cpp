#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<time.h>
#include<stdlib.h>
using namespace std;

double gold=500;
int day;
int cnt,idx=0;

typedef struct Pig{ //猪 
	int id;//编号 
	int ty;//种类 
	int growday;//饲养日期 
	double weight;//重量 
	int pen;//在几号猪圈 
	int virus; 
	struct Pig *next;
}Pig,*PigList;

struct PigPen{//猪圈 
	int sum;//有多少头猪
	int a,b,c;//小花猪、大白花猪、黑猪的数量 
	bool flag;//是否有黑猪 
	int pigid[11];//每头猪的id 
}pigpen[111];

string b[]={"","小花猪","大白花猪","黑猪"};

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
	p->virus = -1;
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
    
    pre->next = p;
 	p->next = NULL;
    return L;
}

//加入固定种类的小猪  
PigList PigListInsert(PigList L,int k) {
    Pig *pre;                     
    pre = L;
    while( pre->next!=NULL )  
	  pre = pre->next;     //查找最后一个结点的前驱节点 
	
    Pig *p;    //要插入的结点为p
    p = (Pig *)malloc(sizeof(Pig));
    p->id = ++idx;//编号 
	p->ty = k;//种类1-3代表三种猪 
	p->growday = 0;//初始饲养日期为0 
	p->weight = rand()%50+20; //随机产生重量 
	p->pen = getpen(p->ty); //为小猪分配猪圈 
	p->virus = -1;
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
    
    pre->next = p;
 	p->next = NULL;
    return L;
}

PigList Insert(PigList L,int id,int ty,int growday,int weight,int pen,int vr) {
    Pig *pre;                     
    pre = L;
	while( pre->next!=NULL )  
	  pre = pre->next; 
	  
    Pig *p;    //要插入的结点为p
    p = (Pig *)malloc(sizeof(Pig));
    p->id=id;
	p->ty=ty;
	p->growday=growday;
	p->weight=weight;
	p->pen=pen;
	p->virus=vr;
	//小猪加入猪圈 
	pigpen[p->pen].pigid[pigpen[p->pen].sum]=idx;
	
	if(p->ty == 1) pigpen[p->pen].a++;
	else if(p->ty == 2) pigpen[p->pen].b++;
	else pigpen[p->pen].c++,pigpen[p->pen].flag=true;
	
	pigpen[p->pen].sum++;//此猪圈内猪的个数增加1 

	pre->next = p;
	p->next = NULL;
  
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
bool vis[111],v[1111];//猪圈是否被感染,猪是否死亡 
 
//经过一天小猪重量增加k千克 
PigList grow(PigList L,double k) {
    Pig *p=L->next;
    int i=0;
    while(p){
        p->growday ++;
		p->weight = p->weight + k; 
		if(p->virus>=0)//发现有小猪感染
		{
			cout<<p->pen<<"号猪圈有猪生病了！"<<endl; 
			p->virus++;
			if(p->virus>=1) vis[p->pen]=1; //大于1天，有传染力
			if(p->virus>=5) v[p->id]=1;//大于5天死亡 
		}

        p=p->next;
    }
    return L;
}

//把编号为k的小猪从猪圈中删除 
void pendel(int x,int k,int t)
{
	int n=pigpen[x].sum;//当前猪圈内猪的数量 
	for(int i=0;i<n;i++)
	{
		if(pigpen[x].pigid[i]==k)//查找到了 
		{
			cout<<x<<"号猪圈有小猪死亡！"<<endl; 
			for(int j=i;j<=n;j++)//后面的编号都前移一位 
				pigpen[x].pigid[j]=pigpen[x].pigid[j+1];
			break;
		}
	}
	pigpen[x].sum--;//当前猪圈内猪的数量减一 
	if(pigpen[x].sum<=0) vis[x]=0;
	if(t==1) pigpen[x].a--;
	if(t==2) pigpen[x].b--;
	if(t==3) pigpen[x].c--;
	if(pigpen[x].c<=0) pigpen[x].flag=0;//没有黑猪了 
	
} 
 
//删除可以出圈的猪 
PigList del(PigList L) {
    
    freopen("output.txt","a",stdout);
    
    double money=0;//本次出圈的猪能卖多少钱 
    int f=1;
	int e[5];
	e[1]=e[2]=e[3]=0;
    while(1)
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
				
				e[p->ty]++;
				if(p->ty==1) x=7;
				else if(p->ty==2) x=6;
				else x=15;
				
				money+=x*(p->weight);
				
				pendel(p->pen,p->id,p->ty);//从猪圈中删除 
				
				f=1;//找到了一个可以出圈的,如果没找到,f=0,循环停止 
				break;
			}		
		}
		if(f==0) break;
		pre->next = p->next;          //删除操作，将其前驱next指向其后继。
  		free(p);
    }
    cout<<"本次出圈";
    for(int i=1;i<=3;i++)
		cout<<b[i]<<e[i]<<"只,"; 
    cout<<"总售价为："<<money<<endl; 
    freopen("CON","w",stdout);
	cout.clear();
    
    gold += money; 
    cout<<"本次出圈的猪总售价为："<<money<<endl; 
    return L;
}

//删除死亡猪 
PigList del(PigList L,int x) {
      
 	Pig *p,*pre;   //pre为前驱结点，p为查找的结点。
	p = L;
    
	while(p->next) 
    {
        pre = p;
        p = p->next;
	    if(p->id==x)
		{			
			v[p->id]=0;	
			pendel(p->pen,p->id,p->ty);//从猪圈中删除 
			pre->next = p->next;          //删除操作，将其前驱next指向其后继。
  			free(p);	
			break;					
		}
    }
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

//查找id为x的元素
int ask(PigList L,int x) {
    Pig *p=L->next;
    int i=0;
    while(p){
        if(p->id==x){
            return 1;
        }
        p=p->next;
    }
    return 0;
}
//id为x的猪标记为生病 
PigList replace(PigList L,int x) {
    Pig *p=L->next;
    int i=0;
    while(p){
        if(p->id==x&&p->virus==-1){
            p->virus++;
            return L;
        }
        p=p->next;
    }
    return L;
}
PigList viru(PigList L)
{
	
	for(int i=0;i<100;i++)
	{
		if(vis[i]){
			//本猪圈全部传染 
			for(int j=0;j<pigpen[i].sum;j++)
			{
				int id=pigpen[i].pigid[j];
				replace(L,id);
			}
			//相邻猪圈15%几率传染
			if(i-1>=0)
				for(int j=0;j<pigpen[i-1].sum;j++)
				{
					int id=pigpen[i-1].pigid[j];
					int pp=rand()%100+1;
					if(pp<=15) 
						replace(L,id);
				}
			if(i+1>=0)
				for(int j=0;j<pigpen[i+1].sum;j++)
				{
					int id=pigpen[i+1].pigid[j];
					int pp=rand()%100+1;
					if(pp<=15) 
						replace(L,id);
				}
		}
	}
	//感染天数>5的小猪，使其死亡
	for(int i=1;i<=idx;i++)
	{
		if(v[i]) 
		{
			L=del(L,i);
		}
	} 
	return L; 
}
void printList(PigList L){
    Pig *p=L->next;
    int i=0;
    while(p){
        cout<<p->id<<' '<<p->ty<<' '<<p->growday
		<<' '<<p->weight<<' '<<p->pen<<' '<<p->virus<<endl; 
        p=p->next;
    }
} 

double a[]={0,5,3,10};
int main(){
	time_t t;
	srand((unsigned) time(&t));
	
	//创建一个链表并初始化 
    PigList list;
    list = PigListInit();
    
    //读取上次数据
	freopen("a.txt","r",stdin);
	cin>>idx;
	int id,ty,gr,pe,vr;
	double we;
	while(cin>>id>>ty>>gr>>we>>pe>>vr)
	{
		Insert(list,id,ty,gr,we,pe,vr);
	}
	freopen("CON","r",stdin);
	cin.clear();
    cout<<"上次小猪信息"<<endl; 
    printList(list);
    cout<<endl;
 	//随机放入cnt头小猪 
	cnt=rand()%10+1;
	//cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)
    PigListInsert(list);
    cout<<"随机放入"<<cnt<<"头小猪后"<<endl; 
    printList(list);
		
	cout<<"\n\n\n\n\n\n\n";
	cout<<"            ======================================================\n";
	cout<<'\n';
	cout<<"                       请选择操作：\n";
	cout<<'\n';
	cout<<"                            1.小猪成长\n";		
	cout<<"                            2.查询某猪圈猪的数量和种类\n";
	cout<<"                            3.查询某猪圈某头猪的状态信息\n";
	cout<<"                            4.统计每种猪的数量、体重、饲养时间分布情况\n";
	cout<<"                            5.查询销售记录和购入记录\n";
	cout<<"                            6.产生猪瘟\n";
	cout<<"                            7.防控\n";
	cout<<"                            8.退出\n";
	cout<<'\n';
	cout<<"            ======================================================\n";

	while(1)
	{				
		int op;
		cin>>op;
		switch(op){
       		case 1:{
       			cout<<"请输入生长天数: ";
				int x;
				cin>>x;
				for(int i=1;i<=x;i++) 
       			{
	       			day++;
	       			int x=rand()%12;
				    list = grow(list,0.1*x);
				  //  printList(list);
				  //  cout<<endl; 
					list = viru(list);//检查是否有猪瘟		
				//	cout<<"传播："<<endl; 
				//	printList(list);
					Pig *p=list->next;
				    int cnt=0;
				    while(p){
				        cnt++;
				        p=p->next;
				    }
				    if(cnt==0) cout<<"猪全部死亡！"<<endl; 
					if(day%90==0) //三个月了,出圈
					{
						del(list);
						cout<<"现有金币数: "<<gold<<endl;
						cout<<"请选择要购入的小猪: "<<endl;
						cout<<"1.小花猪(5元一斤) 2.大白花猪(3元一斤) 3.黑猪(10元一斤) 4.取消"<<endl; 
						cin>>x;
						while(x>4){
							cout<<"无效输入,请重新选择: "; 
							cin>>x;
						} 
						if(x>=1&&x<=3){
							cout<<"请输入要购入的小猪数量: "; 
							cin>>cnt;//=rand()%5+1;
							if(a[x]*cnt>gold) cout<<"金币不足!"<<endl;
							else {
								
								freopen("output.txt","a",stdout);
								cout<<"购入"<<b[x]<<cnt<<"只"<<endl; 
								freopen("CON","a",stdout);
								cout.clear();
							
							//	printList(list);
								gold -= a[x]*cnt;
								while(cnt--)
								{
									PigListInsert(list,x);
									
								}
						     	
						     	
							} 
						}  
						
					}  
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
				freopen("output.txt","r",stdin);
				string s;
				while(cin>>s) cout<<s<<endl;
				freopen("CON", "r", stdin);//输入重定向到控制台
				cin.clear();;
				
				break;
			}
			case 6:{
				int x=rand()%idx+1;
				while(ask(list,x)==0)
					x=rand()%idx;
				list=replace(list,x);//x号得猪瘟 
				break;
			}	
			case 7:{
				cout<<"所有有猪瘟的猪圈编号:"<<endl; 
				for(int i=0;i<100;i++)
					if(vis[i]) cout<<i<<' ';
				cout<<endl;
				cout<<"请输入要杀死的猪圈编号：";
				int x;
				cin>>x;
				while(x<0||x>99)
				{
					cout<<"编号不合法,请重新输入: ";
					cin>>x;
				}
				for(int i=0;i<pigpen[x].sum;i++)
				{
					int id=pigpen[x].pigid[i];
					list=del(list,id);
				} 
				break;
			} 
			case 8:{
				//保存进文件 
				freopen("a.txt","w",stdout);
				cout<<idx<<endl;
				printList(list);
				freopen("CON","a",stdout);
				cout.clear();
				
				//printList(list);
				
				return 0;
			}
			default:break;
		}
		
	}
	
	return 0;
} 




