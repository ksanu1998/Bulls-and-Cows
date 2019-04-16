#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
int my_secret=1729;
vector<int> possible_permutations;
vector<int> unique_set;
struct response
{
	int bulls;
	int cows;
};
struct record
{
	int p;
	int v;
	int f;
};
void swap(record* *xp, record* *yp) 
{ 
    record* temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
void bubbleSort(int n,vector<record*> &arr) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)
 	{       
       for (j = 0; j < n-i-1; j++)
       	{  
           if (arr[j]->f > arr[j+1]->f) 
              swap(&arr[j], &arr[j+1]);
        }
    } 
}
struct response validate_guess(int guess, int secret)
{
	int our_bull_count=0;
	int our_cow_count=0;
	int temp=guess;
	int their_guess_store[4];
	if(secret>1000)
	{
	for(int i=3;i>=0;i--)
		{
			their_guess_store[i]=temp%10;
			temp=temp/10;
		}
	int temp_1=secret;
	int secret_store[4];
	for(int i=3;i>=0;i--)
		{
			secret_store[i]=temp_1%10;
			temp_1=temp_1/10;
		}
	for(int i=0;i<4;i++)
	{
		if(their_guess_store[i]==secret_store[i])
		{
			our_bull_count++;
		}
	}
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(their_guess_store[i]==secret_store[j] && i!=j)
				{
					our_cow_count++;
				}
		}
		
	}
	response out;
	out.bulls=our_bull_count;
	out.cows=our_cow_count;
	return out;
}
else
{
	for(int i=3;i>=0;i--)
		{
			their_guess_store[i]=temp%10;
			temp=temp/10;
		}
	int temp_1=secret;
	int secret_store[4];
	secret_store[0]=0;
	for(int i=3;i>=1;i--)
		{
			secret_store[i]=temp_1%10;
			temp_1=temp_1/10;
		}
	for(int i=0;i<4;i++)
	{
		if(their_guess_store[i]==secret_store[i])
		{
			our_bull_count++;
		}
	}
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(their_guess_store[i]==secret_store[j] && i!=j)
				{
					our_cow_count++;
				}
		}
		
	}
	response out;
	out.bulls=our_bull_count;
	out.cows=our_cow_count;
	return out;
}
}
void validate_their_guess()
{
		int their_guess;
		cout<<"Your guess: ";
		cin>>their_guess;
		response temp;
		temp=validate_guess(their_guess,my_secret);
		cout<<"These are your Bulls: ";
		cout<<temp.bulls<<endl;
		cout<<"These are your Cows: ";
		cout<<temp.cows<<endl;
}
void permute()
{
	for(int i=1000;i<10000;i++)
	{
		int temp=i;
		int check[4];
		for(int i=3;i>=0;i--)
		{
			check[i]=temp%10;
			temp=temp/10;
		}
		bool flag=true;
		for(int k=0;k<4;k++)
		{
			for (int l=k+1;l<4;l++)
			{
				if(check[k]==check[l])
				{
					flag=false;
					break;
				}
			}
			if(flag==false)
				break;
		}
		if(flag)
		{
			possible_permutations.push_back(i);
		}
	}
	
}
void prune(int& our_guess, int our_bulls, int our_cows)
{
	for(int i=0;i<possible_permutations.size();i++)
	{
		vector<int> temp_storage;
		response temp;
		temp=validate_guess(our_guess,possible_permutations[i]);
		if(temp.bulls!=our_bulls || temp.cows!=our_cows)
		{
			possible_permutations.erase(possible_permutations.begin() + i);
		}
		else if(possible_permutations[i]==our_guess)
		{
			possible_permutations.erase(possible_permutations.begin() + i);
		}
		
	}
	
	cout<<"Remaining possibilities: "<<possible_permutations.size()<<endl;
}

void unique_guess_2()
{
	vector<record*> list;
	for(int i=0;i<possible_permutations.size();i++)
	{
				int temp=possible_permutations[i];
				int check;
				for(int j=3;j>=0;j--)
					{
						check=temp%10;
						temp=temp/10;
						bool flag=true;
						for(int k=0;k<list.size();k++)
							{
								if(j==(list[k]->p) && check==(list[k]->v))
									{
					
										flag=false;
										list[k]->f=list[k]->f=+1;
										break;
					
									}
							}
							if(flag)
								{

									struct record* b=new record;
									b->p=j;
									b->v=check;
									b->f=1;
									list.push_back(b);
								}
					}
	}
bubbleSort(list.size(),list);
record* final[4];
int c=0;
final[c]=list[c];
for(int i=1;i<list.size();i++)
{
	bool flag=true;
	for(int j=0;j<c;j++)
	{
		if(list[i]->v==final[j]->v||list[i]->p==final[j]->p)
		{
			flag=false;
			break;
		}
	}
	if(flag)
	{
		c++;
		final[c]=list[i];
	}

	if(c==3)
		break;
}
int sum=0;
for(int i=0;i<4;i++)
{
	int mult;
	if(final[i]->p==3)
		mult=1;
	else if(final[i]->p==2)
		mult=10;
	else if(final[i]->p==1)
		mult=100;
	else if(final[i]->p==0)
		mult=1000;
	sum=sum+((final[i]->v)*mult);

}
unique_set.push_back(sum);
}
int main()
{
	system("clear");
	cout<<"*****Let me guess your 4-digit secret code!****"<<endl;
	cout<<"At every prompt, you could guess my secret code too. All the best!"<<endl;
	//int id;
	int toss;
	int our_bulls;
	int our_cows;
	int count=0;
	int our_initial_guess=1230;
	int our_initial_guess_2=5678;
	permute();
	//cout<<"Your ID: "<<endl;
	//cin>>id;
	cout<<"If you want to start by guessing first, press 0; else press 1"<<endl;
	cout<<"Toss: "<<endl;
	cin>>toss;
		if(toss==0)
			validate_their_guess();
		cout<<"Our guess: ";
		cout<<our_initial_guess<<endl;
		count++;
		cout<<"Bulls: ";
		cin>>our_bulls;
		cout<<"Cows: ";
		cin>>our_cows;
		prune(our_initial_guess,our_bulls,our_cows);
		validate_their_guess();
		if(our_bulls==0&&our_cows==0)
		{

			cout<<"Our guess: ";
			cout<<our_initial_guess_2<<endl;
			count++;
			cout<<"Bulls: ";
			cin>>our_bulls;
			cout<<"Cows: ";
			cin>>our_cows;
			prune(our_initial_guess,our_bulls,our_cows);
			validate_their_guess();
		}
		while(true)
		{
			int our_guess;
			if(possible_permutations.size()==1)
				our_guess=possible_permutations[0];
			else 
					{
						unique_guess_2();
						our_guess=unique_set.back();
					}
			cout<<"Our guess: ";
			cout<<our_guess<<endl;
			count++;
			cout<<"Bulls: ";
			cin>>our_bulls;
			cout<<"Cows: ";
			cin>>our_cows;
			if(our_bulls==4)
			{
				cout<<"Gotcha!"<<endl;
				cout<<"Attempts: "<<count<<endl;
				break;
			}
			prune(our_guess,our_bulls,our_cows);
			validate_their_guess();
		}
		
}