//环境：数据库11g，客户端11g

#include "occi_11g.h"
#include "occi.h"
#include <string>
#include <iostream>
#include <fstream>
#include "time.h"
using namespace std;
using namespace oracle::occi;

//动态库需要安装oracle11g客户端,相关源文件和库文件在.\\oci文件夹
//#pragma comment(lib,"oraocci11")//release版本--多线程(/MT)
#pragma comment(lib,"oraocci11d")//debug版本--多线程调试 DLL (/MDd)

occi_11g::occi_11g(void)
{
}

occi_11g::~occi_11g(void)
{
}

int occi_11g::select()
{
	/*const string userName = "sw_nips";
	const string password = "123456";
	const string connectString = "ccol01";*/

	const string userName = "usr";
	const string password = "password";
	const string connectString = "orcl";

	Environment *env = Environment::createEnvironment(Environment::OBJECT);
	{
		try
		{
			Connection *conn = env->createConnection(userName, password, connectString);
			Statement *stmt = conn->createStatement("select * from table1");
			ResultSet *rs = stmt->executeQuery();

			int count=0;
			//release版本一次性提取数据条数过多会无故退出，可能是有上限，建议不要取太多
			while(rs->next())
			{
				count++;

				if(count==500000)
				{
					cout<<count<<endl;
					count=0;
				}
			}

			stmt->closeResultSet(rs);
			conn->terminateStatement(stmt);
			env->terminateConnection(conn);
		}
		catch (SQLException &sqlExcp)
		{
			cerr <<sqlExcp.getErrorCode()<< ": " << sqlExcp.getMessage() << endl;
		}
		catch (exception &excp)
		{
			cerr << excp.what() << endl;
		}
	}
	Environment::terminateEnvironment(env);

	return 0;
}

int occi_11g::multi_insert1()
{
	const string userName = "usr";
	const string password = "123456";
	const string connectString = "ccol01";

	Environment *env = Environment::createEnvironment(Environment::OBJECT);
	{
		try
		{
			Connection *conn = env->createConnection(userName, password, connectString);
			Statement *stmt = conn->createStatement("insert into test_insert (id, name) values(:1,:2)");

			//注：批量插入条数设置不能太大，会报错
			int insert_row=1000;
			//cout<<stmt->getMaxIterations()<<endl;
			stmt->setMaxIterations(insert_row);//设定最大条数
			stmt->setMaxParamSize(2,100);//设定string类型的最大长度
			//cout<<stmt->getMaxIterations()<<endl;
			//cout<<stmt->getMaxParamSize(2)<<endl;

			string str_name="wangli";
			stmt->setInt(1, 100);
			stmt->setString(2,str_name);

			for(int i=0;i!=insert_row-1;++i)
			{
				stmt->addIteration();
				stmt->setInt(1, 100);
			    stmt->setString(2,str_name);
			}

			stmt->executeUpdate();
            
			conn->terminateStatement(stmt);
			env->terminateConnection(conn);
		}
		catch (SQLException &sqlExcp)
		{
			cerr <<sqlExcp.getErrorCode()<< ": " << sqlExcp.getMessage() << endl;
		}
		catch (exception &excp)
		{
			cerr << excp.what() << endl;
		}
	}
	Environment::terminateEnvironment(env);

	return 0;
}

int occi_11g::multi_insert2()
{
	const string userName = "usr";
	const string password = "123456";
	const string connectString = "ccol01";

	Environment *env = Environment::createEnvironment(Environment::OBJECT);
	{
		try
		{
			Connection *conn = env->createConnection(userName, password, connectString);
			Statement *stmt = conn->createStatement("insert into test_insert (id, name) values(:1,:2)");

			char dnames[][100] = {"Community Outreach", "University Recruiting"};
            ub2 dnameLen[2];
            for (int i = 0; i < 2; i++)
            dnameLen[i] = strlen(dnames[i])+1;
            int ids[2] = {7369, 7654};
            ub2 idLen[2] = {sizeof(ids[0]), sizeof(ids[1])};
            stmt->setDataBuffer(1, ids, OCCIINT, sizeof(ids[0]), idLen);
            stmt->setDataBuffer(2, dnames, OCCI_SQLT_STR, sizeof(dnames[0]), dnameLen);
            stmt->executeArrayUpdate(2); // data for two rows is inserted.

			//occi对于上面的这种类型的数组支持较好，但不支持new出来的数组
		    //const int insert_row=200;
			//ub2 *id=new ub2[insert_row];
			//ub2 *idLen=new ub2[insert_row];
			//string *name=new string[insert_row];
			//ub2 *tstr_len=new ub2[insert_row];
			//char **dnames=new char*[insert_row];

			//for(int i=0;i!=insert_row;++i)
			//{
			//	id[i]=100;
			//	idLen[i]=sizeof(id[i]);
			//	name[i]="wangli";
			//	dnames[i]=new char[100];
			//	memset(dnames[i],0,100);
			//	memcpy(dnames[i],name[i].c_str(),name[i].size());
			//	//dnames[i]=(char *)name[i].c_str();
			//	tstr_len[i]=strlen(dnames[i])+1;
			//}

			////cout<<name[1]<<name[9999]<<endl;

			//stmt->setDataBuffer(1,id,OCCIINT,sizeof(id[0]),idLen);
			//stmt->setDataBuffer(2,dnames,OCCI_SQLT_STR,sizeof(dnames[0]),tstr_len);
			//stmt->executeArrayUpdate(insert_row); // data for two rows is inserted.
            
			conn->terminateStatement(stmt);
			env->terminateConnection(conn);
		}
		catch (SQLException &sqlExcp)
		{
			cerr <<sqlExcp.getErrorCode()<< ": " << sqlExcp.getMessage() << endl;
		}
		catch (exception &excp)
		{
			cerr << excp.what() << endl;
		}
	}
	Environment::terminateEnvironment(env);

	return 0;
}
