#include<iostream>
#include<fstream>
#include<cmath>
#include<climits>
using namespace std;
void read_graph(char [],int[][20],int *);
void find_path(int [][20],int ,int,int[]);
void swap(int *,int *);
class min_heap
       {
        private:
                int *heap;
                int cur_size;
                int max_size;
        public:
                min_heap(int);
                void insert_minheap(int,int ,int[],int,int[]);
                int extract_min(int *,int [],int *,int[]);
                void ifminHeap(int,int[],int []);
                int heap_size();
                void change_heap(int ,int [],int []);
                void show_heap();
                int is_k_inheap(int,int [],int,int *);
      };
int min_heap ::is_k_inheap(int k,int index[],int n,int *p)
     {
       int f=0;
       for(int i=0;i<n;i++)
           {
             if(index[i]==k)
               {
                f=1;
                *p=i;
                break;
              }
           }
             return f;
     }
void min_heap ::show_heap()
        {
          cout<<"\n current Heap:";
          for(int i=0;i<cur_size;i++)
             {
                cout<<" "<<heap[i];
            }
        }
void  min_heap :: change_heap(int pos,int index[],int p[])
      {

         int i=cur_size-1;
         heap[pos]=heap[i];
         --cur_size;
         index[pos]=index[i];
         index[i]=-1;
         p[pos]=p[i];
         p[i]=-1;
         ifminHeap(0,index,p);
      }

int  min_heap :: heap_size()
     {
       return cur_size;
     }
min_heap:: min_heap(int n)
      {
        cur_size=0;
        max_size=n;
        heap=new int[n];
     }
void min_heap :: insert_minheap(int k,int m,int index[],int x,int p[])
        {
          if(cur_size==max_size)
            {
              cout<<"Overflow";
             }
          cur_size++;
          int i=cur_size-1;
          heap[i]=k;
          p[i]=x;
          index[i]=m;
          while(i>0 && heap[(i-1)/2]>heap[i])
               {
                 swap(&heap[i],&heap[(i-1)/2]);
                 swap(&index[i],&index[(i-1)/2]);
                 swap(&p[i],&p[(i-1)/2]);
                 i=i/2;

               }
         }

int min_heap :: extract_min(int *k,int index[],int *prev,int p[])
        {


          int min=heap[0];
          heap[0]=heap[cur_size-1];
          *k=index[0];
          index[0]=index[cur_size-1];
          index[cur_size-1]=-1;

          *prev=p[0];
          p[0]=p[cur_size-1];
          p[cur_size-1]=-1;
          cur_size--;
          ifminHeap(0,index,p);

          return min;
         }
void min_heap :: ifminHeap(int i,int index[],int p[])
        {
            int l=2*i+1;
            int r=l+1;
            int min=i;
            if(l<cur_size && heap[i]>heap[l])
              {
                min=l;
              }
            if(r<cur_size && heap[min]>heap[r])
              {
               min=r;
              }
            if(min!=i)
              {
                swap(&heap[i],&heap[min]);
                swap(&index[i],&index[min]);
                swap(&p[i],&p[min]);
                ifminHeap(min,index,p);
              }
        }
int main()
   {

     int n,graph[20][20],s,d,no_vertex=1;
     char fname[10];
     cout<<"\nEnter the file name:";
     cin>>fname;
     read_graph(fname,graph,&n);
     int parent[n];
     cout<<"\nEnter the source vertex:";
     cin>>s;
     find_path(graph,n,s,parent);
     cout<<"\n\n\nEnter the distination vertex:";
     cin>>d;
     cout<<"\n\nThe path to destination vertex: "<<d<<" from  source vertex: "<<s<<" is:\n";
     cout<<"  "<<d;
     for(int i=d-1;i>0;)
         {
           cout<<" <- "<<parent[i]+1;
           ++no_vertex;
           i=parent[i];

         }
    cout<<"\nNo of edges in the path:"<<no_vertex-1;
     return 0;
   }
void swap(int *x,int *y)
  {
   int t;
   t=*x;
   *x=*y;
   *y=t;
  }

void read_graph(char fname[],int graph[][20],int *n)
 {

    fstream fin;
    int i,j,w;
    fin.open(fname,ios::in|ios::out);
    fin>>*n;
    for(i=0;i<*n;i++)
         {
          for(j=0;j<*n;j++)
              {
                graph[i][j]=-1;
              }

         }
     while(fin)
        {
          fin>>i>>j>>w;
          graph[i-1][j-1]=w;

        }
    cout<<"\nMatrix representation of the Graph:\n";
     for(i=0;i<*n;i++)
         {
           for(j=0;j<*n;j++)
                {
                 cout<<graph[i][j]<<" ";
                }
           cout<<"\n";
         }

  }
void find_path(int graph[][20],int n,int s,int parent[])
     {
       int d[n],i,p[n],index[n],x,z,min,k,pos,prev;
       min_heap ob(n);

       for(i=0;i<n;i++)
          {
           d[i]=-1;
           parent[i]=-1;
           p[i]=-1;
           index[i]=-1;
          }

       d[s-1]=0;
       parent[s-1]=-1;
       x=s-1;
       do
         {
           for(i=0;i<n;i++)
              {
                if(d[i]==-1&&graph[x][i]!=-1)
                  {
                    z=d[x]+graph[x][i];
                    ob.insert_minheap(z,i,index,x,p);
                  }
             }

         min=ob.extract_min(&k,index,&prev,p);
         d[k]=min;

         parent[k]=prev;
       x=k;
         if(ob.is_k_inheap(x,index,ob.heap_size(),&pos)==1)
          {
             ob.change_heap(pos,index,p);

          }
       }while(ob.heap_size()>0);
     cout<<"\nDistance of all the vertices from source vertex "<<s<<" is :";
    for(i=0;i<n;i++)
       {
         cout<<"\nvertex " <<i<<" : "<<d[i];
       }
    cout<<"\nThis is parent array:";
    for(i=0;i<n;i++)
       {
        cout<<"\t i="<<i<<":"<<parent[i];
       }
   }




