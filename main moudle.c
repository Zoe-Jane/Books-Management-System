#include<stdio.h>
#include<windows.h>
#include<string.h>
#include <malloc.h>
#include<ctype.h>
//结构体
struct _BookInf //书本信息
{
	char BookName[100];//书名
	char Writer[50];//作者
	int PressNum;//出版社
	char BookID[13];//书号
	int Prize;//价格
	char IndexNum[50];//索引号
	int Stock;//剩余
	struct BookInf *Next;
}BookInf[101];//<------------------------------------至多输入99个数据 
struct RBookInf //书本信息<--------------------------排序专用结构体 
	{
		char BookName[100];//书名
		char Writer[50];//作者
		int PressNum;//出版社
		char BookID[13];//书号
		int Prize;//价格
		char IndexNum[50];//索引号
		int Stock;//剩余
	}RBookInf[101];//<------------------------------至多输入99个数据
struct _PressInf//<------------------------------出版社信息结构体 
{
	char PressName[100];
	int BookQuantity;
}PressInf[102];//<------------------------------------至多输入99个数据
//对齐函数
void prints(char Array[],int Num)//<---------------用来输出字符数组Array[],Num是输出的字符总数，不足的由空格补足，以达到整齐的效果 
{
	printf("%s",Array);
	int Length=strlen(Array),Remain=Num-Length;
	if(Remain>0)
	{
		for(;Remain>=0;Remain--)
		{
			printf(" ");
		}
	}
 } 
//出版社 
void ReadPress()//读取出版社<---------------------从出版社文件中读取出版社信息并导入出版社信息结构体中 
{
	int Count=0,PressID=0; 
	char TMPPressID[100]={""},PressName[100]={""};
	for(;Count<=101;Count++)//初始化结构体 
    {
    	strcpy(PressInf[Count].PressName," ");
    	PressInf[Count].BookQuantity=0;
	}
	Count=0;
	FILE*  fp;
    fp = fopen("PressInf.db", "r");//开始读取出版社文件 
    if (!fp)
    {
		printf("文件打开错误！");
        return;//<-------------------------------
    }
    strcpy(PressInf[100].PressName,"其他出版社");//将最后一个设为default项 
    while(fscanf(fp,"%s%s",TMPPressID,PressName))//读取出版社文件 
    {
    	if(atoi(TMPPressID)==PressID){break;}
		PressID=atoi(TMPPressID);//转换输入的字符为数字 
		strcpy(PressInf[PressID].PressName,PressName); 
	}
	fclose(fp);
}
//读取数据
void DevideData(char *Readchar,char *BookName,char *Writer,char *PressNum,char *BookID,char *Prize,char *IndexNum,char *Stock) 
{//<---------------------将Readchar中的数据分开， 并且对一些会导致溢出的错误进行防范 
	int Cnt=0,Count=0;
	if(Readchar[Cnt]!='|'){printf("\n数据读取出错，请联系管理员");return;}else{Cnt++;}//<----------
	while(Readchar[Cnt]!='|'){BookName[Count]=Readchar[Cnt];Count++;Cnt++;}Count=0;Cnt++;
	while(Readchar[Cnt]!='|'){Writer[Count]=Readchar[Cnt];Count++;Cnt++;}Count=0;Cnt++;
	while(Readchar[Cnt]!='|'){PressNum[Count]=Readchar[Cnt],Count++;Cnt++;}Count=0;Cnt++;
	while(Readchar[Cnt]!='|'){BookID[Count]=Readchar[Cnt];Count++;Cnt++;}Count=0;Cnt++;
	while(Readchar[Cnt]!='|'){Prize[Count]=Readchar[Cnt];Count++;Cnt++;}Count=0;Cnt++;
	while(Readchar[Cnt]!='|'){IndexNum[Count]=Readchar[Cnt];Count++;Cnt++;}Count=0;Cnt++;
	while(Readchar[Cnt]!='|'){if(Readchar[Cnt]=='\0'){break;}Stock[Count]=Readchar[Cnt];Count++;Cnt++;}
}
void ReadBookInf ()//读取文件 <-----------------------------从书本文件中读取书本信息并导入书本信息结构体中 
{
	int Count=0;
	char Readchar[1000]={""},TMPPressNum[5]={""},TMPPrize[5]={""},TMPStock[5]={""};
	FILE*  fp;
    fp = fopen("BookInf.db", "r");//打开文件 
    if (!fp)
    {
		printf("文件打开错误！");
        return;//<------------------------------- 
    }
	while(fgets(Readchar,1000,fp))//<----从文件中获取信息 
	{
		if(Count>100){break;}
		DevideData(Readchar,BookInf[Count].BookName,BookInf[Count].Writer,TMPPressNum,BookInf[Count].BookID,TMPPrize,BookInf[Count].IndexNum,TMPStock);//<--分开数据 并存入数组 
		BookInf[Count].Stock=atoi(TMPStock);BookInf[Count].Prize=atoi(TMPPrize);BookInf[Count].PressNum=atoi(TMPPressNum);
		Count++;
	}
	fclose(fp);
}
void ShowPressInf()//<-----------------------------------显示出版社信息 
{
	int Count=0;
	for(;Count<100;Count++)
	{
		PressInf[BookInf[Count].PressNum].BookQuantity++;//检测每个出版社的出版图书数量 
	} 
	int PressID=0;
	printf(" ########################################################################################\n");
	printf(" ##########################################出版社########################################\n");
	printf(" ########################################################################################\n\n");
	printf("                  出版社代码         出版社名称                出版书数量                        \n\n");
	for(;PressID<99;PressID++)
	{
		if(strcmp(PressInf[PressID].PressName," ")==0)//对比查看结构体内是否有信息，如果无，继续进入循环 
		{
			continue;
		}
		printf("                      ");
		if(PressID>=10)
    	{
    		printf("%d",PressID);
		}else
		{
			printf("%d ",PressID);
		}
		printf("           ");
		prints(PressInf[PressID].PressName,18);
		printf("             %d\n",PressInf[PressID].BookQuantity);
	}
	printf("\n ########################################################################################\n");
}
void ShowBookInf()//<-----------------------------------显示图书信息 
{
	int Count=0;
	system("cls");
	printf(" ########################################################################################\n");
	printf(" ######################################现有图书信息######################################\n");
	printf(" ########################################################################################\n\n");
	printf("             书 名          作 者    出 版 社            书 号            价格 索引  库存\n\n");
	for(Count=0;Count<100;Count++)
	{
		if(BookInf[Count].Stock==0&&BookInf[Count].Prize==0){continue;}//从结构体中获取信息，并显示出来 
		printf("  ");prints(BookInf[Count].BookName,25);prints(BookInf[Count].Writer,8);prints(PressInf[BookInf[Count].PressNum].PressName,18);printf("ISBN");prints(BookInf[Count].BookID,13);
		printf(" ￥%d ",BookInf[Count].Prize);prints(BookInf[Count].IndexNum,5);printf(" %d\n",BookInf[Count].Stock);
	}
	printf("\n ########################################################################################\n");
}
void ShowSingleBookInf(int Count)//<----------------------显示第Count个结构体中的信息
{
	printf("  ");prints(BookInf[Count].BookName,25);prints(BookInf[Count].Writer,8);prints(PressInf[BookInf[Count].PressNum].PressName,18);printf("ISBN");prints(BookInf[Count].BookID,13);
	printf(" ￥%d ",BookInf[Count].Prize);prints(BookInf[Count].IndexNum,5);printf(" %d\n",BookInf[Count].Stock);
}
void AddBookInf()//<-----------------------添加书本信息 
{
	char Input[2]={""},InputName[100]={""},InputWriter[50]={""},InputBookID[20]={""},TMPPrize[20]={""},InputIndexNum[50]={""},TMPStock[20]={""},TMPPressNum[2]={""};
	int InputPrize=0,InputStock=0,InputPressNum=0,Count=0; 
	printf(" ######################################添加书本##########################################\n");
	printf(" ########################################################################################\n\n");
	printf(" 请输入该的书名称:");
	scanf("%100s",InputName); 
	printf(" 请输入该的书的作者名字:");
	scanf("%50s",InputWriter); 
	printf(" 请输入该的书的书号:");
	printf(" ISBN ");
	scanf("%13s",InputBookID);
	printf(" 请输入该的书的价格:");
	scanf("%20s",TMPPrize);
	InputPrize=atoi(TMPPrize);
	printf(" 请输入该的书的索引号:");
	scanf("%50s",InputIndexNum);
	printf(" 请输入该的书的数量:");
	scanf("%20s",TMPStock);
	InputStock=atoi(TMPStock);//将字符数组转为数字 
	ShowPressInf();//显示书本信息 
	printf("请输入该的书出版社的编号");
	scanf("%2s",TMPPressNum);
	InputPressNum=atoi(TMPPressNum);
	while(strcmp(PressInf[InputPressNum].PressName," ")==0)
	{
		printf("该出版社不存在，是否要添加出版社(Y/N)");//<----------------------------添加出版社 
		scanf("%1s",Input);
		if(Input[0]=='Y'||Input[0]=='y')
		{
			AddPressInf(InputPressNum);
			break;
		}
		if(Input[0]=='N'||Input[0]=='n')
		{
			InputPressNum=100;//选择不添加后 
			break;
		}
	}
    FILE *fp= fopen("BookInf.db", "a");//打开文件 
    if (!fp)
    {
		printf("文件打开错误！");
        return;//<-------------------------------
    }
    fprintf(fp,"|%s|%s|%d|%s|%d|%s|%d|\n",InputName,InputWriter,InputPressNum,InputBookID,InputPrize,InputIndexNum,InputStock);
    fclose(fp);
	printf("添加成功！");
	system("pause");
	ReadPress(); 
	ReadBookInf();system("cls");
} 
int AddPressInf(int InputPressNum)
{
	char TMPInputNum[2]={""},TMPPressName[100]={""}; 
	int InputNum=0;
	if(InputPressNum>100&&InputPressNum<0)
	{
		system("cls");
		ReadPress();
		while(InputPressNum>=100&&InputPressNum<=0)
		{
			printf("请输入新的出版社的编号(1-99)");
			scanf("%2s",TMPInputNum);
			InputPressNum=atoi(TMPInputNum);
		}
	}
	printf("请输入新的出版社的名字");
	scanf("%100s",TMPPressName);
	FILE *fp= fopen("PressInf.db", "a");//打开文件 
    if (!fp)
    {
		printf("文件打开错误！");
        return;//<-------------------------------
    }
    fprintf(fp,"%d %s\n",InputPressNum,TMPPressName);
    fclose(fp);
	return; 
}
void DelBookInf()
{
	int Count=0,Status=101;
	char InputBookID[13]={""},Input[1]={""}; 
	printf("请输入你要删除的书的编号:ISBN "); 
	scanf("%30s",InputBookID);
	for(Count=0;Count<100;Count++)
	{
		if(strcmp(BookInf[Count].BookID,InputBookID)==0)
		{
			printf("请确认是否要删除这本书的资料(Y/N)");
			printf("\n             书 名          作 者    出 版 社            书 号            价格 索引  库存\n\n");
			ShowSingleBookInf(Count);
			scanf("%1s",Input);
			if(Input[0]=='Y'||Input[0]=='y')
			{
				Status=Count;
				break;
			}else {return;};
			memset(BookInf[Status].BookName,0,sizeof(BookInf[Status].BookName));
			memset(BookInf[Status].Writer,0,sizeof(BookInf[Status].Writer));
			memset(BookInf[Status].BookID,0,sizeof(BookInf[Status].BookID));
			memset(BookInf[Status].IndexNum,0,sizeof(BookInf[Status].IndexNum));
			BookInf[Status].PressNum=0;BookInf[Status].Prize=0;BookInf[Status].Stock=0;
			printf("%d,%d,%d",BookInf[Status].PressNum,BookInf[Status].Prize,BookInf[Status].Stock=0);
		}
	}
	system("del BookInf.db");
	system("pause");
	FILE *fp= fopen("BookInf.db", "a");//打开文件 
    if (!fp)
    {
		printf("文件打开错误！");
        return;//<-------------------------------
    }
	for(Count=0;Count<100;Count++)
	{
		if(Count==Status){continue;}
		if(BookInf[Count].Stock==0&&BookInf[Count].PressNum==0){continue;}
		fprintf(fp,"|%s|%s|%d|%s|%d|%s|%d|\n",BookInf[Count].BookName,BookInf[Count].Writer,BookInf[Count].PressNum,BookInf[Count].BookID,BookInf[Count].Prize,BookInf[Count].IndexNum,BookInf[Count].Stock);
	}
	fclose(fp);
	printf("系统将重启以删除该数据！");
	system("pause");
	Restart();
 } 
void ChangeBookInf()
{
	char InputBookID[13]={""},Input[1]={""},Readchar[1000]={""},TMPPressNum[2]={""},TMPPrize[20]={""},TMPStock[20]={""}; 
	int Count=0;
	printf("请输入你要更改的书的编号:ISBN "); 
	scanf("%30s",InputBookID);
	for(Count=0;Count<100;Count++)
	{
		if(strcmp(BookInf[Count].BookID,InputBookID)==0)
		{
			printf("请确认是否要修改这本书的信息(Y/N)");
			printf("\n             书 名          作 者    出 版 社            书 号            价格 索引  库存\n\n");
			ShowSingleBookInf(Count);
			scanf("%1s",Input);
			if(Input[0]=='Y'||Input[0]=='y')
			{
				printf("请在文本文件中修改并保存！");
				FILE *fpc= fopen("Result.tmp", "a");
				fprintf(fpc,"|%s|%s|%d|%s|%d|%s|%d|\n",BookInf[Count].BookName,BookInf[Count].Writer,BookInf[Count].PressNum,BookInf[Count].BookID,BookInf[Count].Prize,BookInf[Count].IndexNum,BookInf[Count].Stock);
				fclose(fpc);
				printf("\n请务必在保存后继续！");
				system("notepad.exe Result.tmp");
				memset(BookInf[Count].BookName,0,sizeof(BookInf[Count].BookName));
				memset(BookInf[Count].Writer,0,sizeof(BookInf[Count].Writer));
				memset(BookInf[Count].BookID,0,sizeof(BookInf[Count].BookID));
				memset(BookInf[Count].IndexNum,0,sizeof(BookInf[Count].IndexNum));
				system("pause");
				FILE *fpo= fopen("Result.tmp", "r");
				if (!fpo)
 			   {
					printf("文件打开错误！");
  			        return;//<-------------------------------
  				}
  				fgets(Readchar,1000,fpo);
  				DevideData(Readchar,BookInf[Count].BookName,BookInf[Count].Writer,TMPPressNum,BookInf[Count].BookID,TMPPrize,BookInf[Count].IndexNum,TMPStock);
  				BookInf[Count].PressNum=atoi(TMPPressNum);BookInf[Count].Prize=atoi(TMPPrize);BookInf[Count].Stock=atoi(TMPStock);
				fclose(fpo);
				system("del Result.tmp");
				system("del BookInf.db");
				FILE *fp= fopen("BookInf.db", "a");//打开文件 
   				if (!fp)
   				{
					printf("文件打开错误！");
   			    	return;//<-------------------------------
    			}
				for(Count=0;Count<100;Count++)
				{
					if(BookInf[Count].PressNum==0&&BookInf[Count].Stock==0){continue;}
					fprintf(fp,"|%s|%s|%d|%s|%d|%s|%d|\n",BookInf[Count].BookName,BookInf[Count].Writer,BookInf[Count].PressNum,BookInf[Count].BookID,BookInf[Count].Prize,BookInf[Count].IndexNum,BookInf[Count].Stock);
				}
				fclose(fp);
				printf("修改完成！");
				system("pause");
				break;
			}else{break;}
		}
	}
	ReadPress();
	ReadBookInf();system("cls");
}
void ManageBookInf()
{
	ReadPress(); 
	ReadBookInf();
	system("cls");
	ShowBookInf();
	char Input[2]={""}; 
	printf("                                  输入<1>增加书本                \n"); 
	printf("                                 输入<2>修改书本信息              \n"); 
	printf("                                  输入<3>删除书本                 \n");
	printf("                                 输入<4>返回主菜单                \n");
	printf(" ########################################################################################\n");
	printf("  请输入你想进行的操作：");
	scanf("%1s",Input);
	if(Input[0]=='1'){system("cls");AddBookInf();}else
	if(Input[0]=='2'){ChangeBookInf();}else
	if(Input[0]=='3'){DelBookInf();}else
	if(Input[0]=='4'){system("cls");IndexPage();}
	ManageBookInf();
} 
void ManagePressInf()
{
	ShowPressInf();
	int Count=0;
	char Input[2]={""}; 
	printf(" ########################################################################################\n");
	do 
	{
		printf("  请输入出版社编号以显示出版社旗下图书:");
		scanf("%2s",Input);
	}while(strcmp(PressInf[atoi(Input)].PressName," ")==0);
	printf("\n             书 名          作 者    出 版 社            书 号            价格 索引  库存\n\n");
	for(Count=0;Count<100;Count++)
	{
		if(BookInf[Count].PressNum==atoi(Input))
		{
			ShowSingleBookInf(Count);
		}
	}
	system("pause");
	IndexPage(); 
}
void QueryWriter()//<------------------------------------------------------------------- 
{
	ShowBookInf();
	char Input[20]={""}; 
	int Count=0,Count1=0;
	printf("  请输入作者名称:");
	scanf("%20s",Input);
	printf(" ########################################################################################\n");
	printf("\n             书 名          作 者    出 版 社            书 号            价格 索引  库存\n\n");
	for(Count1=0;Count1<100;Count1++)
	{
		if(strstr(BookInf[Count1].Writer,Input)!=NULL)
		{
			ShowSingleBookInf(Count1);
			Count=1;
		}
	}
	if(Count==0)
	{
		printf("找不到该作者的书籍\n");
	}
	printf("\n ########################################################################################\n");
	system("pause");
	IndexPage(); 
}
void QueryBookName()
{
	ShowBookInf();
	char Input[20]={""}; 
	int Count=0,Count1=0;
	printf("  请输入书本名称:");
	scanf("%20s",Input);
	printf(" ########################################################################################\n");
	printf("\n             书 名          作 者    出 版 社            书 号            价格 索引  库存\n\n");
	for(Count1=0;Count1<100;Count1++)
	{
		if(strstr(BookInf[Count1].BookName,Input)!=NULL)
		{
			ShowSingleBookInf(Count1);
			Count=1;
		}
	}
	if(Count==0)
	{
		printf("找不到该名字的书籍\n");
	}
	printf("\n ########################################################################################\n");
	system("pause");
	IndexPage(); 
}
void Rank(int Sequence)
{
	if(Sequence==0)//<-------------------------------------------------------------
	{
		int Count1=0,Count2=0,Size=100;
	    for(Count1=1;Count1<Size-1;Count1++)
	    {
    	    for(Count2=0;Count2<Size-Count1;Count2++)
    	    {
    	        if(strcmp(RBookInf[Count2].BookID,RBookInf[Count2+1].BookID)>0)
    	        {
    	            RBookInf[101]=RBookInf[Count2];
    	            RBookInf[Count2]=RBookInf[Count2+1];
     	           RBookInf[Count2+1]=RBookInf[101];
        	    }
        	} 
    	}
	}else
	if(Sequence==1)
	{
		int Count1=0,Count2=0,Size=100;
		for(Count1=0;Count1<Size;Count1++)
		{
			for(Count2=1;Count2<Size;Count2++)
			{
				if(strcmp(RBookInf[Count2].BookID,RBookInf[Count2-1].BookID)>0)
				{
					RBookInf[101]=RBookInf[Count2];
					RBookInf[Count2]=RBookInf[Count2-1];
					RBookInf[Count2-1]=RBookInf[101];
				}
			}
		}
	}else
	if(Sequence==2)
	{
		int Count1=0,Count2=0,Size=100;
	    for(Count1=1;Count1<Size-1;Count1++)
	    {
    	    for(Count2=0;Count2<Size-Count1;Count2++)
    	    {
    	        if(RBookInf[Count2].Prize>RBookInf[Count2+1].Prize)
    	        {
    	            RBookInf[101]=RBookInf[Count2];
    	            RBookInf[Count2]=RBookInf[Count2+1];
     	           RBookInf[Count2+1]=RBookInf[101];
        	    }
        	} 
    	}
	}else
	if(Sequence==3)
	{
		int Count1=0,Count2=0,Size=100;
		for(Count1=0;Count1<Size;Count1++)
		{
			for(Count2=1;Count2<Size;Count2++)
			{
				if(RBookInf[Count2].Prize>RBookInf[Count2-1].Prize)
				{
					RBookInf[101]=RBookInf[Count2];
					RBookInf[Count2]=RBookInf[Count2-1];
					RBookInf[Count2-1]=RBookInf[101];
				}
			}
		}
	}
	int Count=0;
	system("cls");
	printf(" ########################################################################################\n");
	printf(" ######################################现有图书信息######################################\n");
	printf(" ########################################################################################\n\n");
	printf("             书 名          作 者    出 版 社            书 号            价格 索引  库存\n\n");
	for(Count=0;Count<100;Count++)
	{
		if(RBookInf[Count].Stock==0&&RBookInf[Count].Prize==0){continue;}
		printf("  ");prints(RBookInf[Count].BookName,25);prints(RBookInf[Count].Writer,8);prints(PressInf[RBookInf[Count].PressNum].PressName,18);printf("ISBN");prints(RBookInf[Count].BookID,13);
		printf(" ￥%d ",RBookInf[Count].Prize);prints(RBookInf[Count].IndexNum,5);printf(" %d\n",RBookInf[Count].Stock);
	}
	printf("\n ########################################################################################\n");
 } 
void RankBookInf()
{ 
	int Cnt=0;
	for(;Cnt<=99;Cnt++)
	{
		RBookInf[Cnt].PressNum=BookInf[Cnt].PressNum;RBookInf[Cnt].Prize=BookInf[Cnt].Prize;
		RBookInf[Cnt].Stock=BookInf[Cnt].Stock;
		strcpy(RBookInf[Cnt].BookName,BookInf[Cnt].BookName);
		strcpy(RBookInf[Cnt].Writer,BookInf[Cnt].Writer);
		strcpy(RBookInf[Cnt].BookID,BookInf[Cnt].BookID);
		strcpy(RBookInf[Cnt].IndexNum,BookInf[Cnt].IndexNum);
	}
	for(;;)
	{
		char Input[1]={""}; 
		printf("    <1>入库日期升序  <2>书号升序  <3>书号降序  <4>价格升序  <5>价格降序  <6>返回主界面 ");
		printf("\n ########################################################################################\n");
		printf("\n\n请输入你要进行的操作：") ;
		scanf("%1s",&Input);
		if(Input[0]=='1'){system("cls");ReadBookInf();ShowBookInf();RankBookInf();}else
		if(Input[0]=='2'){system("cls");Rank(0);}else
		if(Input[0]=='3'){system("cls");Rank(1);}
		if(Input[0]=='4'){system("cls");Rank(2);}else
		if(Input[0]=='5'){system("cls");Rank(3);}else
		if(Input[0]=='6'){system("cls");IndexPage();}
	}
}
void OutputExcel()
{
	printf("\n ########################################################################################\n");
	printf("      正在导出并打开Excel");
	system("del Output.csv");
	system("cls");
	FILE* fp;
    fp = fopen("Output.csv", "a");//打开文件 
    if (!fp)
    {
		printf("导出失败！");
        return;//<-------------------------------
    }
    int Count=0;
    fprintf(fp,"书名,作者,出版社,书号,价格,索引,库存\n");
	for(;Count<100;Count++)
	{
		if(BookInf[Count].PressNum==0&&BookInf[Count].Stock==0){continue;}
		fprintf(fp,"%s,%s,%s,%s,%d,%s,%d\n",BookInf[Count].BookName,BookInf[Count].Writer,PressInf[BookInf[Count].PressNum].PressName,BookInf[Count].BookID,BookInf[Count].Prize,BookInf[Count].IndexNum,BookInf[Count].Stock);
	}
	fclose(fp);
	printf("导出完成！");
	system("pause");
	system("start Output.csv");
	system("cls");
	IndexPage();
 }
