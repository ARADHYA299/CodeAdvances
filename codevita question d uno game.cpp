# include<iostream>
# include<vector>
# include<string>
# include<unordered_map>
# include<algorithm>

using namespace std;



int main(){
	int N;
	cin >> N;
	
	vector<string> names(N);
	
	unordered_map<string,int> name2idx;
	for(int i=0;i<N;i++){
		cin>> names[i];
		name2idx[names[i]] = i;
	}
	
	vector<int> skill(N);
	for(int i=0;i<N;i++){
		cin>>skill[i];
	}
	
	int N1;
	cin>>N1;
	
	vector<int> friend_pair(N,-1);
	for(int i=0;i<N1;i++){
		string a,b;
		cin>>a>>b;
		int ai = name2idx[a] , bi = name2idx[b];
		
		friend_pair[ai] = bi;
		friend_pair[bi] = ai;
	}
	int N2;
	cin>>N2;
	
	vector<pair<int,int>>rivals(N2);
	for(int i=0;i<N2;i++){
		string a,b;
		cin>>a>>b;
		rivals[i] = {name2idx[a],name2idx[b]};
	}
	
	
	int limit;
	cin>>limit;
	
	vector<vector<int>> units;
	vector<int> unit_skill;
	vector<bool> used(N,false);
	
	for(int i=0;i<N;i++){
		if(used[i]) continue;
		vector<int> u;
		u.push_back(i);
		
		int total = skill[i];
		used[i] = true;
		
		if(friend_pair[i] != -1 && !used[friend_pair[i]]){
			int j = friend_pair[i];
			u.push_back(j);
			
			total += skill[j];
			used[j] = true;
			
		}
		
		units.push_back(u);
		unit_skill.push_back(total);
	}
	
	int U = units.size();
	vector<int> rival_mask(U,0);
	
	for(int i=0;i<N2;i++){
		int a = rivals[i].first , b = rivals[i].second;
		
		int ua = -1 , ub = -1;
		
		for(int j=0;j<U;j++){
			if(find(units[j].begin(),units[j].end(),a) != units[j].end()) ua = j;
			if(find(units[j].begin(),units[j].end(),b) != units[j].end()) ub = j;
			
		}
		
		if(ua != -1 && ub != -1){
			rival_mask[ua] |= (1<<ub);
			rival_mask[ub] |= (1<<ua);
		}
	}
	
	int ans = 0;
	int full = 1 << U;
	for(int mask = 0;mask<full;mask++){
		int total_skill = 0;
		bool ok = true;
		for(int i=0;i<U;i++){
			if(mask&(1<<i)){
				total_skill += unit_skill[i];
				if(total_skill>limit){ok = false ; break;}
				if(rival_mask[i]&mask){ok = false ; break;}
				}
			}
			
			if(ok){
				int count = 0;
				for(int i=0;i<U;i++){
					if(mask&(1<<i)) count += units[i].size();
				}
				
				if(count>ans) ans = count;
			}
		}
		
	cout<<ans<<endl;
	return 0;
}