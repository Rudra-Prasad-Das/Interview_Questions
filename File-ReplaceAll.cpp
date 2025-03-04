string simplifyKeys(unordered_map<string,string>& templates,string key){
	
	string val = templates[key];
	string newVal = "";
	string internalKey = "";
	bool intKeyPresent = false;
	int size  = val.size();
	for(int i=0;i<size;i++)
	{
		if(val[i]=='%'){
			if(intKeyPresent == true){
				if(templates.count(internalKey)){
					newVal += simplifyKeys(templates,internalKey);
				}
				internalKey = "";
				intKeyPresent = false;
			} else {
				intKeyPresent = true;
			}
		} else {
		    if(intKeyPresent == false) newVal += val[i];
			else internalKey += val[i];
		}
	}
	
	
	return templates[key] = newVal;
 }

string solve(unordered_map<string,string>& templates,string simplify) {
	
	for(auto it: templates){
		simplifyKeys(templates,it.first);
	}
	
	string ans = "";
	string key="";
	bool keyFound = false;
	for(int i=0; i<simplify.size();i++){
		if(simplify[i]=='%') {
			if(keyFound == true) {
				ans += templates[key];
				key = "";
				keyFound = false;
			} else {
				keyFound = true;
			} 
		} else {
			if(keyFound == false) ans += simplify[i];
			else key += simplify[i];
		}
	}
	return ans;
}
