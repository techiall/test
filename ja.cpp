#include <iostream>
#include <string>
using namespace std;

const string delete_java_path[] = {
	"wmic ENVIRONMENT where \"name='JAVA_HOME'\" delete",
	"wmic ENVIRONMENT where \"name='CLASS_PATH'\" delete"
};

string set_path[] = {

	"wmic ENVIRONMENT create name=\"JAVA_HOME\","
	"username=\"<system>\","
	"VariableValue=\""
	,

	"wmic ENVIRONMENT create name=\"CLASS_PATH\","
	"username=\"<system>\","
	"VariableValue=\""
	".;%JAVA_HOME%\\lib\\tools.jar;"
	"%JAVA_HOME%\\lib\\dt.jar;\""
	,

	"wmic ENVIRONMENT where \"name='Path' and username='<system>'\" "
	"set VariableValue=\""
	"%Path%;%JAVA_HOME%\\jre\\bin;%JAVA_HOME%\\bin\""
	,
};

int main(void)
{
#ifdef _DEBUG
	freopen("in.txt", "r", stdin);
#endif // _DEBUG

	cout << "右键管理员身份打开\n";
	cout << "输入 Java 安装目录：";
	string tmp;
	getline(cin, tmp);
	if (tmp[tmp.length() - 1] == '\\')
		tmp.pop_back();

	set_path[0].append(tmp).append("\"");
	for (int i = 0; i < sizeof(delete_java_path) / sizeof(*delete_java_path); i++)
		system(delete_java_path[i].c_str());

	for (int i = 0; i < sizeof(set_path) / sizeof(*set_path); i++)
		system(set_path[i].c_str());
	return 0;
}
