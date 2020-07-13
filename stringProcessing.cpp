#include "stringProcessing.h"

//the main written below was used for testing
/*
int main()
{
	string s1 = "%^%$hahahah9384#$@hah";
	string s2 = "YIKEsss@($&342###";
	string s3 = "#(YiKE@(342###";
	//cout<<s1<<endl;
	cout<<"mod: "<<stripNonAlphaNum(s1)<<endl;
	cout<<"mod: "<<stripNonAlphaNum(s2)<<endl;
	cout<<"mod: "<<stripNonAlphaNum(s3)<<endl;
	return 0;
}
*/
//stripNonAlphaNum
//param: string s
//return: concatednated string
//concatenates string such that the non number or letter characters
//are removed from the front and back of the string
string stripNonAlphaNum(string s)
{
	while((s.length() > 0) and ((s.at(0) < 'a' or s.at(0) > 'z') and
		 (s.at(0) < '0' or s.at(0) > '9') and (s.at(0) < 'A' or s.at(0)
		 >'Z'))){
		s.erase(0, 1);
	}
	int end = s.length() - 1;
	while((end > 0) and ((s.at(end) < 'a' or s.at(end) > 'z') and
		 (s.at(end) < '0' or s.at(end) > '9') and (s.at(end) < 'A' or s.at(end)
		 >'Z'))){
		s.pop_back();
		end--;
	}
	return s;
}

