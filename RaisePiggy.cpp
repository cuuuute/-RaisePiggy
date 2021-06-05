#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<time.h>
#include<stdlib.h>
using namespace std;

double gold=500;
int day;
int cnt,idx=0,start;

typedef struct Pig//�� 
{ 
	int id;//��� 
	int ty;//���� 
	int growday;//�������� 
	double weight;//���� 
	int pen;//�ڼ�����Ȧ 
	int virus; 
	struct Pig *next;
}Pig,*PigList;

struct PigPen//��Ȧ
{ 
	int sum;//�ж���ͷ��
	int a,b,c;//С������׻������������ 
	bool flag;//�Ƿ��к��� 
	int pigid[11];//ÿͷ���id 
}pigpen[111];

string b[]={"","С����","��׻���","����"};

//���ұ��Ϊid���� 
void find(PigList L,int id)
{
    Pig *p=L->next;
    int i=0;
    while(p)
	{
    	if(p->id==id)
		 {//�ҵ��������Ϣ 
    		cout<<"����Ϊ ";	
			if(p->ty==1)cout<<"С����";
			if(p->ty==2)cout<<"��׻���";
			if(p->ty==3) cout<<"����";
			cout<<"����Ϊ "<<p->weight<<"kg,";
			cout<<"����ʱ��Ϊ "<<p->growday/30<<"��"<<p->growday%30<<"��";
   		
    		return;
    	}
        p=p->next;
    } 
} 
 
//Ϊ����С�������Ȧ 
int getpen(int k)
{
	int x=-1;
	//С����,��׻���
	if(k==1||k==2)
	{
		for(int i=0;i<100;i++)
		{
			//��û�к������Ȧ�������������ٵ�Ȧ 
			if(!pigpen[i].flag && (x==-1||pigpen[i].sum<pigpen[x].sum))
				x=i;
		}
		//û���ҵ��޺���Ļ���ȫ������ 
		if(x==-1||pigpen[x].sum==10)
			return -1; 
	}
	else //���� 
	{
		for(int i=0;i<100;i++)
		{
			//���ȷ����Ѿ��к�����û��������Ȧ 
			if(pigpen[i].flag && pigpen[i].sum<10)
			{
				return i;
			}	
		}
		//���û���ҵ�,�Ҹ��յķ������ 
		for(int i=0;i<100;i++)
		{
			if(pigpen[i].sum == 0)
				return i;
		}
	}
	
	return x;
}

//����С���� 
PigList PigListInsert(PigList L) 
{
    Pig *pre;                     
    pre = L;
    while( pre->next!=NULL )  
	  pre = pre->next;     //�������һ������ǰ���ڵ� 
	
    Pig *p;    //Ҫ����Ľ��Ϊp
    p = (Pig *)malloc(sizeof(Pig));
    p->id = ++idx;//��� 
	p->ty = rand()%3+1;//����1-3���������� 
	p->growday = 0;//��ʼ��������Ϊ0 
	p->weight = rand()%50+20; //����������� 
	p->pen = getpen(p->ty); //ΪС�������Ȧ 
	p->virus = -1;
//	cout<<p->id<<' '<<p->ty<<' '<<p->growday<<' '<<p->weight<<' '<<p->pen<<endl; 
	if(p->pen==-1) 
	{
		cout<<"��Ȧ����/�����,�޷����룡����"<<endl; 
		return L;
	}
	else 
	{
		//С�������Ȧ 
		pigpen[p->pen].pigid[pigpen[p->pen].sum]=idx;
		
		if(p->ty == 1) pigpen[p->pen].a++;
		else if(p->ty == 2) pigpen[p->pen].b++;
		else pigpen[p->pen].c++,pigpen[p->pen].flag=true;
		
		pigpen[p->pen].sum++;//����Ȧ����ĸ�������1 
	}
    
    pre->next = p;
 	p->next = NULL;
    return L;
}

//����̶������С��  
PigList PigListInsert(PigList L,int k) 
{
    Pig *pre;                     
    pre = L;
    while( pre->next!=NULL )  
	  pre = pre->next;     //�������һ������ǰ���ڵ� 
	
    Pig *p;    //Ҫ����Ľ��Ϊp
    p = (Pig *)malloc(sizeof(Pig));
    p->id = ++idx;//��� 
	p->ty = k;//����1-3���������� 
	p->growday = 0;//��ʼ��������Ϊ0 
	p->weight = rand()%50+20; //����������� 
	p->pen = getpen(p->ty); //ΪС�������Ȧ 
	p->virus = -1;
//	cout<<p->id<<' '<<p->ty<<' '<<p->growday<<' '<<p->weight<<' '<<p->pen<<endl; 
	if(p->pen==-1) 
	{
		cout<<"��Ȧ����/�����,�޷����룡����"<<endl; 
		return L;
	}
	else 
	{
		//С�������Ȧ 
		pigpen[p->pen].pigid[pigpen[p->pen].sum]=idx;
		
		if(p->ty == 1) pigpen[p->pen].a++;
		else if(p->ty == 2) pigpen[p->pen].b++;
		else pigpen[p->pen].c++,pigpen[p->pen].flag=true;
		
		pigpen[p->pen].sum++;//����Ȧ����ĸ�������1 
	}
    
    pre->next = p;
 	p->next = NULL;
    return L;
}

//����һֻ��ȫ��֪������ 
PigList Insert(PigList L,int id,int ty,int growday,int weight,int pen,int vr) 
{
    Pig *pre;                     
    pre = L;
	while( pre->next!=NULL )  
	  pre = pre->next; 
	  
    Pig *p;    //Ҫ����Ľ��Ϊp
    p = (Pig *)malloc(sizeof(Pig));
    p->id=id;
	p->ty=ty;
	p->growday=growday;
	p->weight=weight;
	p->pen=pen;
	p->virus=vr;
	//С�������Ȧ 
	pigpen[p->pen].pigid[pigpen[p->pen].sum]=idx;
	
	if(p->ty == 1) pigpen[p->pen].a++;
	else if(p->ty == 2) pigpen[p->pen].b++;
	else pigpen[p->pen].c++,pigpen[p->pen].flag=true;
	
	pigpen[p->pen].sum++;//����Ȧ����ĸ�������1 

	pre->next = p;
	p->next = NULL;
  
    return L;
}

//�����ʼ��
PigList PigListInit() 
{
    Pig *L;
    L = (Pig *)malloc(sizeof(Pig));   //������ռ�
    if(L==NULL)
	{    //�ж�����ռ��Ƿ�ʧ��
    	cout<<"����ռ�ʧ��!"<<endl; 
        exit(0);    //���ʧ�����˳�����
    }
    L->next = NULL;          //��next����ΪNULL,��ʼ����Ϊ0�ĵ�����
    return L;
}

bool vis[111];//��Ȧ��Ⱦ��������Ȧ�Ƿ񱻸�Ⱦ
bool v[1111];//�����������������Ƿ����� 
 
//����һ��С����������kǧ�� 
PigList grow(PigList L,double k) 
{
    Pig *p=L->next;
    int i=0;
    while(p){
        p->growday ++;
		p->weight = p->weight + k; 
		if(p->virus>=0)//������С���Ⱦ
		{
			cout<<p->pen<<"����Ȧ���������ˣ�"<<endl; 
			p->virus++;
			if(p->virus>=1) vis[p->pen]=1; //����1�죬�д�Ⱦ��
			if(p->virus>=5) v[p->id]=1;//����5������ 
		}

        p=p->next;
    }
    return L;
}

//�ѱ��Ϊk��С�����Ȧ��ɾ�� 
void remove(int x,int k,int t,int f)
{
	int n=pigpen[x].sum;//��ǰ��Ȧ��������� 
	for(int i=0;i<n;i++)
	{
		if(pigpen[x].pigid[i]==k)//���ҵ��� 
		{
			if(f) cout<<x<<"����Ȧ��С��������"<<endl; 
			for(int j=i;j<=n;j++)//����ı�Ŷ�ǰ��һλ 
				pigpen[x].pigid[j]=pigpen[x].pigid[j+1];
			break;
		}
	}
	pigpen[x].sum--;//��ǰ��Ȧ�����������һ 
	if(pigpen[x].sum<=0) vis[x]=0;
	if(t==1) pigpen[x].a--;
	if(t==2) pigpen[x].b--;
	if(t==3) pigpen[x].c--;
	if(pigpen[x].c<=0) pigpen[x].flag=0;//û�к����� 
	
} 
 
//�������п��Գ�Ȧ���� 
PigList sell(PigList L) 
{
    
    freopen("output.txt","a",stdout);
    
    double money=0;//���γ�Ȧ������������Ǯ 
    int f=1;
	int e[5];
	e[1]=e[2]=e[3]=0;
    while(1)
	{       
	 	Pig *p,*pre;   //preΪǰ����㣬pΪ���ҵĽ�㡣
    	p = L;
    	f=0;
	    while(p->next) 
        {
	        pre = p;
	        p = p->next;
	        //��������,���Գ�Ȧ 
	        if(p->weight>150||p->growday>365)
			{
				double x;//���� 
				
				e[p->ty]++;
				if(p->ty==1) x=7;
				else if(p->ty==2) x=6;
				else x=15;
				
				money+=x*(p->weight);
				
				remove(p->pen,p->id,p->ty,0);//����Ȧ��ɾ�� 
				
				f=1;//�ҵ���һ�����Գ�Ȧ��,���û�ҵ�,f=0,ѭ��ֹͣ 
				break;
			}		
		}
		if(f==0) break;
		pre->next = p->next;          //ɾ������������ǰ��nextָ�����̡�
  		free(p);
    }
    cout<<"���γ�Ȧ";
    for(int i=1;i<=3;i++)
		cout<<b[i]<<e[i]<<"ֻ,"; 
    cout<<"���ۼ�Ϊ��"<<money<<endl; 
    freopen("CON","w",stdout);
	cout.clear();
    
    gold += money; 
    cout<<"���γ�Ȧ�������ۼ�Ϊ��"<<money<<endl; 
    return L;
}

//ɾ�������� 
PigList remove(PigList L,int x)
{
      
 	Pig *p,*pre;   //preΪǰ����㣬pΪ���ҵĽ�㡣
	p = L;
    
	while(p->next) 
    {
        pre = p;
        p = p->next;
	    if(p->id==x)
		{			
			v[p->id]=0;	
			remove(p->pen,p->id,p->ty,1);//����Ȧ��ɾ�� 
			pre->next = p->next;          //ɾ������������ǰ��nextָ�����̡�
  			free(p);	
			break;					
		}
    }
    return L;
}

//ͳ�Ƶ�k��������������ء�����ʱ��ֲ����
void cla(PigList L,int k)
{
	int s=0;//����
	double w=0;//����
	int mint=10000,maxt=0;//ʱ��
	int v[111]={0};//��Ȧ�ֲ� 
	Pig *p=L->next;
	if(p==NULL) 
	{
		cout<<"��Ȧ��û�д�����!!!"<<endl; 
		return;
	}
    int i=0;
    while(p)
	{
    	//�ҵ���һ�� 
    	if(p->ty==k) 
		{
    		s++;//������һ 
    		w+=p->weight;//���������� 
    		v[p->pen]=1;//�����������Ȧ�ı��
    		mint=min(mint,p->growday);//��С���� 
    		maxt=max(maxt,p->growday);//������ 
    	} 
        p=p->next;
    } 
    if(k==1)cout<<"С����";
	if(k==2)cout<<"��׻���";
	if(k==3) cout<<"����";
	cout<<"������Ϊ"<<s;
	if(s==0) 
	{
		cout<<endl<<endl;
		return;
	}
	cout<<",������Ϊ"<<w<<"\n������С��������ʱ��Ϊ"<<mint<<"��,��������"
	<<maxt<<"��\n�ֲ�����Ȧ�� ";
	for(int i=0;i<100;i++)
		if(v[i]) cout<<i<<' ';
	cout<<endl<<endl; 
}

//����idΪx��Ԫ��
int ask(PigList L,int x)
{
    Pig *p=L->next;
    int i=0;
    while(p)
	{
        if(p->id==x)
		{
            return 1;
        }
        p=p->next;
    }
    return 0;
}
//idΪx������Ϊ���� 
PigList replace(PigList L,int x) 
{
    Pig *p=L->next;
    int i=0;
    while(p)
	{
        if(p->id==x&&p->virus==-1)
		{
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
		if(vis[i])
		{
			//����Ȧ50%���ʴ�Ⱦ 
			for(int j=0;j<pigpen[i].sum;j++)
			{
				int id=pigpen[i].pigid[j];
				int pp=rand()%100+1;
				if(pp<=50) 
					replace(L,id);
			}
			//������Ȧ15%���ʴ�Ⱦ
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
	//��Ⱦ����>5��С��ʹ������
	for(int i=1;i<=idx;i++)
	{
		if(v[i]) 
		{
			L=remove(L,i);
		}
	} 
	return L; 
}
void printList(PigList L)
{
    Pig *p=L->next;
    int i=0;
    while(p)
	{
        cout<<p->id<<' '<<p->ty<<' '<<p->growday
		<<' '<<p->weight<<' '<<p->pen<<' '<<p->virus<<endl; 
        p=p->next;
    }
} 


double a[]={0,400,300,500};//���� 

void page()
{
	cout<<"            ======================================================\n";
	cout<<'\n';
	cout<<"                       ��ѡ�������\n";
	cout<<'\n';
	cout<<"                            1.С��ɳ�\n";		
	cout<<"                            2.��ѯĳ��Ȧ�������������\n";
	cout<<"                            3.��ѯĳ��Ȧĳͷ���״̬��Ϣ\n";
	cout<<"                            4.ͳ��ÿ��������������ء�����ʱ��ֲ����\n";
	cout<<"                            5.��ѯ���ۼ�¼�͹����¼\n";
	cout<<"                            6.��������\n";
	cout<<"                            7.����\n";
	cout<<"                            8.�˳�\n";
	cout<<'\n';
	cout<<"            ======================================================\n";

}


void cls()							//system("cls")�����������ҵĵ����Ϸ�����Ӧ�ó�����󣨵�ַΪ0xc0000142�� 
{									//����ҷ�����ʹ���������������ö�ռ��еĽ���취 
	cout<<"\n\n\n\n\n\n\n";
}

int main()
{
	time_t t;
	srand((unsigned) time(&t));
	
	//����һ��������ʼ�� 
    PigList list;
    list = PigListInit();
    
    //��ȡ�ϴ�����
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
    cout<<"�ϴ�С����Ϣ"<<endl; 
    printList(list);
    cout<<endl;
 	//�������cntͷС�� 
	cnt=rand()%10+1;
	//cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)
    PigListInsert(list);
    cout<<"�������"<<cnt<<"ͷС���"<<endl; 
    printList(list);
//	page();
	int flag=0;
	while(1)
	{					
		cls();//cout 
		page();	
		int op;
		cin>>op;
		switch(op)
		{
       		case 1:
			{
       			cout<<"��������������: ";
				int x;
				cin>>x;
				for(int i=1;i<=x;i++) 
       			{
	       			day++;
	       			int x=rand()%12;
				    list = grow(list,0.1*x);
				  //  printList(list);
				  //  cout<<endl; 
					list = viru(list);//����Ƿ�������		
				//	cout<<"������"<<endl; 
				//	printList(list);
					Pig *p=list->next;
				    int cnt=0;
				    while(p)
					{
				        cnt++;
				        p=p->next;
				    }
				    if(start&&flag&&cnt==0) flag=0,cout<<"����������ʼ"<<day-start<<"�죬��Ȧ��������ȫ��GG��"<<endl; 
					if(day%90==0) //��������,��Ȧ
					{
						sell(list);
						cout<<"���н����: "<<gold<<endl;
						cout<<"��ѡ��Ҫ�����С��: "<<endl;
						cout<<"1.С����(400Ԫһֻ) 2.��׻���(300Ԫһֻ) 3.����(500Ԫһֻ) 4.ȡ��  ��ps���̵���۵�С������20-50kg����������~��"<<endl; 
						cin>>x;
						while(x>4)
						{
							cout<<"��Ч����,������ѡ��: "; 
							cin>>x;
						} 
						if(x>=1&&x<=3)
						{
							cout<<"������Ҫ�����С������: "; 
							cin>>cnt;//=rand()%5+1;
							if(a[x]*cnt>gold) cout<<"��Ҳ���!"<<endl;
							else 
							{
								
								freopen("output.txt","a",stdout);
								gold -= a[x]*cnt;
								cout<<"����"<<b[x]<<cnt<<"ֻ,Ǯ��ʣ����Ϊ"<<gold<<"Ԫ��"<<endl; //�ļ���¼ 
								freopen("CON","a",stdout);
								cout.clear();
								cout<<"����"<<b[x]<<cnt<<"ֻ,Ǯ��ʣ����Ϊ"<<gold<<"Ԫ��"<<endl;//����̨��ʾ�������û� 
							//	printList(list);
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
			case 2:
			{
				int x;
				cout<<"��������Ȧ��ţ�";
   		      	cin>>x;
   		      	int br=0;
				while(x<0||x>99)
				{
					if(x==-1) 
					{
						br=1;
						break;
					}
					cout<<"��Ų��Ϸ�,����������(����-1������ҳ��): ";
					cin>>x;
				}
				if(br==1) 
				{
					cls();	
					page();	
					break;
				}
   		      	cout<<"����Ȧ��"<<pigpen[x].sum<<"ͷ�������к���"<<pigpen[x].c
				<<"ͷ��С����"<<pigpen[x].a<<"ͷ����׻���"<<pigpen[x].b<<"ͷ\n\n";

				break;
			}
			case 3:
			{
				int x;
				cout<<"��������Ȧ��ţ�";
   		      	cin>>x;
   		      	int br=0;
				while(x<0||x>99)
				{
					if(x==-1) 
					{
						br=1;
						break;
					}
					cout<<"��Ų��Ϸ�,����������(����-1������ҳ��): ";
					cin>>x;
				}
				if(br) 
				{
					cls();	
					page();	
					break;
				}
   		      	
   		      	cout<<"����Ȧ��"<<pigpen[x].sum<<"ͷ��,��������ı��: ";
				int y=x;
				br=0;
				cin>>x;
				while(x<0||x>=pigpen[y].sum)
				{
					if(x==-1) 
					{
						br=1;
						break;
					}
					cout<<"��Ų��Ϸ�,����������(����-1������ҳ��): ";
					cin>>x;
				}
				if(br) 
				{
					cls();	
					page();	
					break;
				}
				//cout<<pigpen[x].pigid[y]<<endl;
				find(list,pigpen[y].pigid[x]);
				break;
			}
			case 4:
			{
				cla(list,1);
				cla(list,2);
				cla(list,3);
				break;
			} 
			case 5:
			{
				freopen("output.txt","r",stdin);
				string s;
				while(cin>>s) cout<<s<<endl;
				freopen("CON", "r", stdin);//�����ض��򵽿���̨
				cin.clear();
				
				break;
			}
			case 6:
			{
				int x=rand()%idx+1;
				while(ask(list,x)==0)
					x=rand()%idx;
				start=day;
				flag=1;
				list=replace(list,x);//x�ŵ����� 
				break;
			}	
			case 7:
			{
				cout<<"��������������Ȧ���:"<<endl; 
				for(int i=0;i<100;i++)
					if(vis[i]) cout<<i<<' ';
				cout<<endl;
				cout<<"������Ҫɱ������Ȧ��ţ�";
				int x;
				cin>>x;
				int br=0;
				while(x<0||x>99)
				{
					if(x==-1) 
					{
						br=1;
						break;
					}
					cout<<"��Ų��Ϸ�,����������(����-1������ҳ��): ";
					cin>>x;
				}
				if(br) 
				{
					cls();	
					page();	
					break;
				}
				for(int i=0;i<pigpen[x].sum;i++)
				{
					int id=pigpen[x].pigid[i];
					list=remove(list,id);
				} 
				break;
			} 
			case 8:
			{
				//������ļ� 
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





