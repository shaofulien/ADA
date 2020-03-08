#include <cryptominisat5/cryptominisat.h>
#include <assert.h>
#include <vector>
#include <array>
#include <iostream>
#include <climits>
#include <numeric>  
#include <vector>
#include <memory>
#include <queue>
#include <tuple>
#include <set>
using namespace std;
using namespace CMSat;
SATSolver solver;
vector<CMSat::Lit> lit_buf;
int R,C;
void Init(int n) { solver.new_vars(n + 1); }

void AddClause(std::vector<int> v) {
    lit_buf.clear();
    lit_buf.reserve(v.size());
    for (int x : v) lit_buf.emplace_back(abs(x), x < 0);
    solver.add_clause(lit_buf);
}

bool Solve() { return solver.solve() == CMSat::l_True; }

int GetResult(int id) {
    auto r = solver.get_model()[id];
    return r == CMSat::l_True ? 1 : r == CMSat::l_False ? -1 : 0;
}

tuple<int,int,int,int> get_edges_id(int cell_id){
    int h1,h2,v1,v2;
    int totoal_H = C*(R+1);
    int v_offest = (cell_id-1)/C;
    h1 = cell_id;
    h2 = cell_id+C;
    v1 = cell_id+totoal_H+v_offest;
    v2 = v1+1;
    return make_tuple(h1,h2,v1,v2);
}

//vector<vector<int> > cell_clauses(int cell_value,tuple cell_edges)

void add_cell_constraint(int cell_id,int cell_value){
    tuple<int,int,int,int> cell_edges;
    cell_edges = get_edges_id(cell_id);
    int e1 = get<0>(cell_edges);
    int e2 = get<1>(cell_edges);
    int e3 = get<2>(cell_edges);
    int e4 = get<3>(cell_edges);
    if (cell_value == 0){
        std::vector<int> c1{-e1};
        std::vector<int> c2{-e2};
        std::vector<int> c3{-e3};
        std::vector<int> c4{-e4};
        AddClause(c1);
        AddClause(c2);
        AddClause(c3);
        AddClause(c4);
    }
    else if(cell_value==1){
        std::vector<int> c1{-e1,-e2};
        std::vector<int> c2{-e1, -e3};
        std::vector<int> c3{-e1, -e4};
        std::vector<int> c4{-e2, -e3};
        std::vector<int> c5{-e2, -e4};
        std::vector<int> c6{-e3, -e4};
        std::vector<int> c7{e1, e2, e3, e4};
        AddClause(c1);
        AddClause(c2);
        AddClause(c3);
        AddClause(c4);
        AddClause(c5);
        AddClause(c6);
        AddClause(c7);
    }            
    else if(cell_value==2){
        std::vector<int> c1{e2, e3, e4};
        std::vector<int> c2{e1, e3, e4};
        std::vector<int> c3{e1, e2, e4};
        std::vector<int> c4{e1, e2, e3};
        std::vector<int> c5{-e2, -e3, -e4};
        std::vector<int> c6{-e1, -e3, -e4};
        std::vector<int> c7{-e1, -e2, -e4};
        std::vector<int> c8{-e1, -e2, -e3};
        AddClause(c1);
        AddClause(c2);
        AddClause(c3);
        AddClause(c4);
        AddClause(c5);
        AddClause(c6);
        AddClause(c7);
        AddClause(c8);
    } 
    else if(cell_value==3){
        std::vector<int> c1{e1, e2};
        std::vector<int> c2{e1, e3};
        std::vector<int> c3{e1, e4};
        std::vector<int> c4{e2, e3};
        std::vector<int> c5{e2, e4};
        std::vector<int> c6{e3, e4};
        std::vector<int> c7{-e1, -e2, -e3, -e4};
        AddClause(c1);
        AddClause(c2);
        AddClause(c3);
        AddClause(c4);
        AddClause(c5);
        AddClause(c6);
        AddClause(c7);
    }
    
}

std::vector<int> get_edges_corner(int i,int j){
    int right_edge = -1;
    int left_edge = -1;
    int up_edge = -1;
    int down_edge = -1;
    int totoal_H = C*(R+1);
    std::vector<int> v;
    if(j<C){
        right_edge = (j+1)+i*C;
        v.push_back(right_edge);
    }
    if(j>0){
        left_edge =  (j+1)+i*C-1;
        v.push_back(left_edge);
    }
    if(i<R){
        down_edge = totoal_H+ j+i*(C+1)+1;
        v.push_back(down_edge);
    }
    if(i>0){
        up_edge = totoal_H+j+(i-1)*(C+1)+1 ;
        v.push_back(up_edge);
    }
    return v;
}
void add_corner_constraint(int i,int j){
    //4 corner case
    std::vector<int> edges;
    edges = get_edges_corner(i,j);
    if (edges.size()==2){
        int v1 = edges[0];
        int v2 = edges[1];
        vector<int> c1{-v1, v2};
        vector<int> c2{v1, -v2};
        AddClause(c1);
        AddClause(c2);

    }
    
    else if(edges.size()==3){
        int v1 = edges[0];
        int v2 = edges[1];
        int v3 = edges[2];
        vector<int> c1{-v1,-v2,-v3};
        vector<int> c2{-v1,v2,v3};
        vector<int> c3{v1,-v2,v3};
        vector<int> c4{v1,v2,-v3};
        
        AddClause(c1);
        AddClause(c2);
        AddClause(c3);
        AddClause(c4);

    } 
    
    else if(edges.size()==4){
        int v1 = edges[0];
        int v2 = edges[1];
        int v3 = edges[2];
        int v4 = edges[3];
        vector<int> c1{-v1, v2, v3, v4};
        vector<int> c2{v1, -v2, v3, v4};
        vector<int> c3{v1, v2, -v3, v4};
        vector<int> c4{v1, v2, v3, -v4};
        vector<int> c5{-v1, -v2, -v3};
        vector<int> c6{-v1, -v2, -v4};
        vector<int> c7{-v1, -v3, -v4};
        vector<int> c8{-v2, -v3, -v4};
        AddClause(c1);
        AddClause(c2);
        AddClause(c3);
        AddClause(c4);
        AddClause(c5);
        AddClause(c6);
        AddClause(c7);
        AddClause(c8);

    }

}
vector<int> get_nebor_edge(int visit){
    int totoal_H = C*(R+1);
    vector<int> a,b,res;
    if (visit<=totoal_H){
        //horizontal line
        int r = (visit-1)/C;
        int c = (visit-1)%C;
        a = get_edges_corner(r,c);
        b = get_edges_corner(r,c+1);
    }
    else{
        //vertical line
        int r= (visit-totoal_H-1)/(C+1);
        int c=(visit-totoal_H-1)%(C+1);
        a = get_edges_corner(r,c);
        b = get_edges_corner(r+1,c);
    }
    for (int i=0; i<a.size();i++){
        if (a[i]!=visit and GetResult(a[i])==1){
            res.push_back(a[i]);
        }
    }
    for (int i=0; i<b.size();i++){
        if (b[i]!=visit and GetResult(b[i])==1){
            res.push_back(b[i]);
        }
    }
    return res;

}
void countline_rec(set<int>* s, int visit ,vector<int>* v){
    v->push_back(-visit);
    vector<int> edges;
    edges = get_nebor_edge(visit);
    /*
    for (auto it=s->begin(); it != s->end(); ++it) 
        cout << ' ' << *it; 
    cout<<endl;*/
    if (s->count(visit)>0){
        s->erase(visit);
        /*
        for (int i=0;i<edges.size();i++){
            cout<<edges[i]<<' ';
        }
        cout<<endl;*/
        for (int i=0;i<edges.size();i++){
            if (GetResult(edges[i])==1 and s->count(edges[i])>0 ){
                //cout<<edges[i]<<"->";
                countline_rec(s,edges[i],v);
            }
        }
    }

}

int main() {

    solver.set_num_threads(4);
    ios_base::sync_with_stdio(false);  
    cin.tie(nullptr);
    bool is_print=1;
    cin>>R>>C;
    char table[R][C];
    for (int i=0; i<R;i++){
        for (int j=0; j<C;j++){
            cin>>table[i][j];
        }
    }

    Init(2*R*C+R+C);

    //cell constraint
    int cell_id,cell_value;
    for (int i=0; i<R;i++){
        for (int j=0; j<C;j++){
            cell_id = C*i+j+1;
            if (table[i][j]=='.') continue;
            else {
                cell_value = (int) (table[i][j]-'0');
                add_cell_constraint(cell_id,cell_value);
            }
        }
    }
    //corner constraint
    for (int i=0; i<R+1;i++){
        for(int j=0;j<C+1;j++){
            add_corner_constraint(i,j);
        }
    }
    
    
    while(true) {
        lbool ret = solver.solve();

        //Use solution here. print it, for example.
        set<int> myset;
        int start_v;
        for(int v_id =1; v_id<=(2*R*C+R+C); v_id++){
            if (GetResult(v_id)==1){
                myset.insert(v_id);
                start_v = v_id;
            }
        } 
        std::vector<int > uncomplete_loop;
        countline_rec(&myset,start_v,&uncomplete_loop);
        if (myset.size()==0) {
            //cout<<"success";
            break;
        }   
        else{   
            AddClause(uncomplete_loop); 
            while (!myset.empty()){

                uncomplete_loop.clear();
                auto it = myset.begin();
                countline_rec(&myset,*it,&uncomplete_loop);
                AddClause(uncomplete_loop); 
            }
            

            /*
            for (int q=0;q<uncomplete_loop.size();q++){
                cout<<uncomplete_loop[q]<<"->";
            }     
            cout<<endl;  */
        }

    }




    
    //print output
    /*
    if(is_print){
        cout<<endl<<"__________solution___________"<<endl<<endl;
        for (int i=0; i<2*R+1;i++){
            for (int j=0; j<2*C+1;j++){
                if(i%2==1 and j%2==1){
                    cout<<table[i/2][j/2];
                }
                else if (i%2==0 and j%2==0){
                    cout<<"+";
                }
                else if (i%2==1 and j%2==0){
                    int c = (j/2)+1;
                    int r = (i)/2;
                    int totoal_H = C*(R+1);
                    if(GetResult(c+r*(C+1)+totoal_H)==1){
                        cout<<"|";
                    }
                    else{
                        cout<<" ";
                    }
                }      
                else if (i%2==0 and j%2==1){
                    int c = (j+1)/2;
                    int r = (i/2);
                    if (GetResult(c+r*C)==1){
                        cout<<"-";
                    }
                    else{
                        cout<<" ";
                    }
                }
            }
            cout<<endl;           
        }
    }*/
    
    for (int i=0; i<2*R+1;i++){
        for (int j=0; j<2*C+1;j++){
            if (i%2==1 and j%2==0){
                int c = (j/2)+1;
                int r = (i)/2;
                int totoal_H = C*(R+1);
                if(GetResult(c+r*(C+1)+totoal_H)==1){
                    cout<<1;
                }
                else{
                    cout<<0;
                }
            }      
            else if (i%2==0 and j%2==1){
                int c = (j+1)/2;
                int r = (i/2);
                if (GetResult(c+r*C)==1){
                    cout<<1;
                }
                else{
                    cout<<0;
                }
            }
        }          
    }

    

    return 0;
}
