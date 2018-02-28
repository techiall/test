#include <stdio.h>
#include <string.h>

//#define DEBUG

void delect_system_variables(const char *name)
{
	char cmd[300] = {0};
	sprintf(cmd, "wmic ENVIRONMENT where \"name='%s'\" delete", name);

#ifdef DEBUG
	printf("%s\n", cmd);
#else
	system(cmd);
#endif // DEBUG

}

void create_system_variables(const char *name, const char *value, 
			     const char *use = "system")
{
	char cmd[300] = {0};
	sprintf(cmd,
		"wmic ENVIRONMENT create name=\"%s\","
		"username=\"<%s>\","
		"VariableValue=\"%s\"",
		name, use, value
	);
#ifdef DEBUG
	printf("%s\n", cmd);
#else
	system(cmd);
#endif // DEBUG;

}

void set_system_variables(const char *name, const char *value, 
			  const char *use = "system")
{
	char cmd[300] = {0};
	sprintf(cmd,
		"wmic ENVIRONMENT where \"name='%s' and username='<%s>'\" "
		"set VariableValue=\"%s\"",
		name, use, value
	);
#ifdef DEBUG
	printf("%s\n", cmd);
#else
	system(cmd);
#endif // DEBUG

}

void config_java()
{
#ifdef DEBUG
	char java_home_value[50] = "C:\\Program Files\\Java\\jdk1.8.0_141";
#else
	char java_home_value[50];
	scanf("%s", java_home_value);
#endif

	int len = strlen(java_home_value);
	if (java_home_value[len - 1] == '\\') {
		java_home_value[len - 1] == '\0';
	}

	const char *java_home_name = "JAVA_HOME";
	const char *class_path_name = "CLASS_PATH";

	delect_system_variables(java_home_name);
	delect_system_variables(class_path_name);

	create_system_variables(java_home_name, java_home_value);

	char class_path_value[100] = {0};
	sprintf(class_path_value, ".;%%%s%%\\lib\\tools.jar;%%%s%%\\lib\\dt.jar;", java_home_name, java_home_name);
	create_system_variables(class_path_name, class_path_value);

	const char *path_name = "Path";
	char path_value[100] = {0};
	sprintf(path_value, "%%%s%%;%%%s%%\\jre\\bin;%%%s%%\\bin", path_name, java_home_name, java_home_name);
	set_system_variables(path_name, path_value);
}

int main(void)
{
#ifndef DEBUG
	puts("右键管理员身份打开");
#endif // DEBUG

	config_java();
	return 0;
}

/*
wmic ENVIRONMENT create name="JAVA_HOME",username="<system>",VariableValue="D:\Program Files\Java\jdk1.8.0_141"
wmic ENVIRONMENT create name="CLASS_PATH",username="<system>",VariableValue=".;%JAVA_HOME%\lib\tools.jar;%JAVA_HOME%\lib\dt.jar;"
wmic ENVIRONMENT where "name='Path' and username='<system>'" set VariableValue="%Path%;%JAVA_HOME%\jre\bin;%JAVA_HOME%\bin"
*/
