#include<iostream>
#include<sstream>
#include<string.h>
#include<stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include<math.h>
	using namespace std;
	//declaring the class
	string s1, st, num;//input strings
	int i=2,j=0;
	int brackets=1;
	float a=0;

	class glistnode
	{
 		public:
 		bool tag;
 		string atom;
 		glistnode *down, *next;
	};

	glistnode *makelist();//declaring the makelist function
	
	float innum(string);

	void display(glistnode *p)
	{
		glistnode *x;
	 	while((p)!=NULL)
 		{
  			if((p->tag)==0);
  			{
				cout<<p->atom;
  			}
  			if((p->tag)==1)
  			{
   				x=p->down;
   				display(x);
  			}
  			p=p->next;
 		}
	}
	
	//declaring value class

	class Value 	
	{
		public:
		int tag;
		float val;
		glistnode* link;
	};

	//declaring env here

	class Env
	{
		public:
		Value* table[26];
		Env* parent;
		// the constructor
		Env() 
		{
			for(int z=0; z<26; z++)
			table[z]=NULL;
			parent=NULL;
		}
	};

	//declaring add function

	void add(char x, Value val_new, Env &e) 
	{
		Value *p = new Value;
		p->tag=val_new.tag;
		p->link=val_new.link;
		p->val=val_new.val;
		e.table[x-'a']=p;
		//cout<<p->val<<"from add\n";
	}

	//declaring find function

	Value find(char x, Env &e) 
	{
		if (e.table[x-'a'] != NULL) 
		{
			//cout<<"found";
			return *(e.table[x-'a']);
		}
		else 
		{
			if (e.parent == NULL) 
			{
				cout << "Entry " << x << " not found in symbol table " << endl;
			}
			else 
			{
				cout << " Looking in parent environment " << endl;
				return find(x, *(e.parent));
			}
		}
	}

	Value evalNode(glistnode *p, Env& e);//prototype

	Value evalList(glistnode *p, Env& e); //prototype	
	//declaring Evalnode here

	Value evalNode(glistnode *p, Env& e) 
	{ 
		if((p->tag)==1)
		{
			return evalList(p->down,e); //check this
		}
		string s=p->atom;
		int code=static_cast<int>(s[0]);
		if(((p->atom).length())==1&&(code>96&&code<123))
		{
			string s=p->atom;
			int code=static_cast<int>(s[0]);
			char x=s[0];
			return find(x,e);
		}
		else
		{
			float k=innum(p->atom);
			Value *v=new Value;
			v->tag=0;
			v->val=k;
			return *v;
		}
	};

	//declaring Evalist here
	Value *bret=new Value;
	Value *wret=new Value;
	Value evalList(glistnode *p, Env& e) 
	{ 
		if (p->atom == "begin") 
		{
			//p=p->next;
			while((p->next)!= NULL) 
			{
				Value v=evalNode(p->next,e);
				p = p->next;
				if((p->next)==NULL)
				bret->val=v.val;
				bret->tag=v.tag;
				continue;
			}
			
			return *bret;
		}
		if (p->atom == "lambda") 
		{
			Value new_val;
			new_val.tag=1;
			new_val.link=p;
			return new_val;
		}
		if (p->atom=="if")
		{
			p=p->next;
			Value ret=evalNode(p,e);
			p=p->next;
			Value iftrue=evalNode(p,e);
			Value *istrue=new Value;
			istrue->val=iftrue.val;
			istrue->tag=0;
			p=p->next;
			Value iffalse=evalNode(p,e);
			Value *isfalse=new Value;
			isfalse->val=iffalse.val;
			isfalse->tag=0;
			if(ret.val==1)
			return *istrue;
			else
			return *isfalse;
		}
		
		if (p->atom=="<=")
		{
			p=p->next;
			Value v1=evalNode(p,e);
			Value v2=evalNode(p->next,e);
			//cout<<v1.val;
			//cout<<v2.val;		
			Value *gottrue=new Value;
			gottrue->val=1;
			gottrue->tag=0;
			Value *gotfalse=new Value;
			gotfalse->val=0;
			gotfalse->tag=0;
			if(v1.val<=v2.val)
				return *gottrue;
			else
				return *gotfalse;
		}
		
		if (p->atom==">=")
		{
			p=p->next;
			Value v1=evalNode(p,e);
			Value v2=evalNode(p->next,e);
			//cout<<v1.val;
			//cout<<v2.val;		
			Value *gottrue=new Value;
			gottrue->val=1;
			gottrue->tag=0;
			Value *gotfalse=new Value;
			gotfalse->val=0;
			gotfalse->tag=0;
			if(v1.val>=v2.val)
				return *gottrue;
			else
				return *gotfalse;
		}

		if (p->atom==">")
		{
			p=p->next;
			Value v1=evalNode(p,e);
			Value v2=evalNode(p->next,e);
			//cout<<v1.val;
			//cout<<v2.val;		
			Value *gottrue=new Value;
			gottrue->val=1;
			gottrue->tag=0;
			Value *gotfalse=new Value;
			gotfalse->val=0;
			gotfalse->tag=0;
			if(v1.val>v2.val)
				return *gottrue;
			else
				return *gotfalse;
		}


		if (p->atom=="<")
		{
			p=p->next;
			Value v1=evalNode(p,e);
			Value v2=evalNode(p->next,e);
			//cout<<v1.val;
			//cout<<v2.val;		
			Value *gottrue=new Value;
			gottrue->val=1;
			gottrue->tag=0;
			Value *gotfalse=new Value;
			gotfalse->val=0;
			gotfalse->tag=0;
			if(v1.val<v2.val)
				return *gottrue;
			else
				return *gotfalse;
		}

		if (p->atom=="==")
		{
			p=p->next;
			Value v1=evalNode(p,e);
			Value v2=evalNode(p->next,e);
			//cout<<v1.val;
			//cout<<v2.val;		
			Value *gottrue=new Value;
			gottrue->val=1;
			gottrue->tag=0;
			Value *gotfalse=new Value;
			gotfalse->val=0;
			gotfalse->tag=0;
			if(v1.val==v2.val)
				return *gottrue;
			else
				return *gotfalse;
		}


		if(p->atom=="define")
		{
			Value v=evalNode(p->next->next,e);
			string s=p->next->atom;
			char name=s[0];
			//cout<<name;
			add(name,v,e);
			p=p->next;
			Value *re=new Value;
			re->val=v.val;
			re->tag=0;
			return *re;
		}
		
		if(p->atom=="set")
		{
			Value v=evalNode(p->next->next,e);
			string s=p->next->atom;
			char name=s[0];
			//cout<<name;
			add(name,v,e);
			p=p->next;
			Value *re=new Value;
			re->val=v.val;
			re->tag=0;
			return *re;
		}
		
		if(p->atom=="while")
		{
			Value v=evalNode(p->next,e);
			while(v.val!=0)
			{
				v=evalNode(p->next,e);
				if(v.val==0)
				break;
				Value l=evalNode(p->next->next,e);
				wret->val=l.val;
				wret->tag=0;
			}
			return *wret;
		}
		
		string s=p->atom;
		int code=static_cast<int>(s[0]);
		if(((p->atom).length())==1&&(code>96&&code<123))
		{
			char x=s[0];
			cout<<x<<"\n";
			Value q=find(x,e);
			glistnode *z=new glistnode;
			z=q.link;
			Env e1;
			//e1->parent=e;
			glistnode *s=new glistnode;
			s=p->next;
			glistnode *r=new glistnode;
			r=z->next->down;
			while(s!=NULL)
			{
				string y=r->atom;
				char o=y[0];
				add(o,evalNode(s,e),e1);
				s=s->next;
				r=r->next;
			}
			return evalNode(z->next->next,e1);
		}
		//( ( lambda ( x y ) ( * x y ) ) 6 3 )
		
		if((p->tag)==1)
		{
			Value a=evalList(p->down,e);
			glistnode *c=new glistnode;
			c=a.link;
			Env e1;
			//e1->parent=e;
			glistnode *sp=new glistnode;
			if(p->next->tag==1)
			sp=p->next->down->next;
			else
			sp=p->next;
			glistnode *rp=new glistnode;
			rp=c->next->down;
			while(sp!=NULL)
			{
				string y=rp->atom;
				char o=y[0];
				add(o,evalNode(sp,e),e1);
				sp=sp->next;
				rp=rp->next;
			}
			return evalNode(c->next->next,e1);
		}
		if(p->atom=="+")
		{
			Value val1=evalNode(p->next,e);
			Value val2=evalNode(p->next->next,e);
			Value *sum=new Value;
			sum->tag=0;
			sum->val=val1.val+val2.val;
			return *sum;
		}
		if(p->atom=="*")
		{
			Value val1=evalNode(p->next,e);
			Value val2=evalNode(p->next->next,e);
			Value *prod=new Value;
			prod->tag=0;
			prod->val=(val1.val)*(val2.val);
			return *prod;
		}
		if(p->atom=="/")
		{
			Value val1=evalNode(p->next,e);
			Value val2=evalNode(p->next->next,e);
			Value *quot=new Value;
			quot->tag=0;
			quot->val=(val1.val)/(val2.val);
			return *quot;
		}
		if(p->atom=="-")
		{
			Value val1=evalNode(p->next,e);
			Value val2=evalNode(p->next->next,e);
			Value *diff=new Value;
			diff->tag=0;
			diff->val=(val1.val)-(val2.val);
			return *diff;
		}
		if(p->atom=="%")
		{
			Value val1=evalNode(p->next,e);
			Value val2=evalNode(p->next->next,e);
			Value *rem=new Value;
			rem->tag=0;
			int k=val1.val;
			int s=val2.val;
			rem->val=(k)%(s);
			return *rem;
		}
	}
	
	int main()
	{
		string n;  		
		//cin>>n;		
		getline(cin,s1);
  		glistnode *p= new glistnode;
  		p=makelist();//calling makelist
  		//display(p);
		Env e;
		Value z=evalList(p,e);
		cout<<z.val;
	}
	void input()
	{
 		int m;
 		m=s1.length();
 		st.erase(0,m);
 		while((s1[i]!=32)&&(s1[i]!=0))
 		{
  			st=st+s1[i];
  			if(s1[i]!=0)
  			i++;
 		}
  		if(s1[i]!=0)
  		i++;
		//cout<<st;
	}

	float innum(string num)
	{
		float ans=(float)(atof(num.c_str()));
		return ans;
		/*cout<<ans;
		string dot=".";
		a=0;
		int m;
 		m=num.length();
 		cout<<m;
 		while(j<((num.length())))
 		{
			st.erase(0,m);
			st=num[j];
			cout<<st<<"\n";
			if(strcmp(st.c_str(),dot.c_str())==0)
			{
				m=j;
				cout<<m;
				break;
			}
			j=j+1;
			cout<<j<<"\n";
			
		}
		j=0;
		while(j<((num.length())))
		{
			st.erase(0,m);
			st=num[j];
			while(strcmp(st.c_str(),dot.c_str())!=0)
			{
				st=num[j];
				float k=st[0];
				k=k-48;
				a=a+(k*pow(10,m-j-1));
				j=j+1;
			}
			if((strcmp(st.c_str(),dot.c_str())==0))
			{
				j=j+1;
				int u=1;
				while(j<((num.length())))
				{
					st.erase(0,m);
					st=num[j];
					float k=st[0];
					k=k-48;
					a=a+(k*pow(10,-u));
					j=j+1;
					u=u+1;
				}
			}
		j=0;
		return a;
		//cout<<st;
		}*/
	}
	glistnode *makelist()
	{
		string left="(";
    		string right=")";
    		//glistnode *p=new glistnode;
    		glistnode *p,*head;
    		p=NULL;
    		while(brackets!=0)
   		{
			//cout<<brackets<<"\n";
    			input();
   		if(strcmp(left.c_str(),st.c_str())==0)
   		{
			brackets=brackets+1;
    			if(p==NULL)
    			{
     				head=new glistnode;
     				p=head;
     				p->tag=1;
     				p->down=makelist();
				continue;
    			}
    
    			else
    			{
     				p->next=new glistnode;
     				p=p->next;
     				p->tag=1;
     				p->down=makelist();
				continue;
    			}
   		}
     		if(((strcmp(right.c_str(),st.c_str())!=0)&&(strcmp(left.c_str(),st.c_str())!=0)))
    		{
     			if(p==NULL)
     			{
      				head=new glistnode;
      				p=head;
      				p->tag=0;
      				p->down=NULL;
      				p->atom=st;
     			}
     			else
     			{
      				p->next=new glistnode;
      				p=p->next;
      				p->tag=0;
      				p->down=NULL;
      				p->atom=st;
     			}
    		}
    		else
		{
			brackets=brackets-1;
    			p->next=NULL;
    			return head;
   		} 
 		}
	}

