#include  <iostream>
#include  <cstdlib>
#include  <fstream>
using  namespace  std;
int normalize(string& reg)
{
    const string errorSymbols = ".*+?";
    int numberOfSpeshalChar=0;
    if(reg[reg.size()]=='\\')return -1;
    if(errorSymbols.find(reg[0],1)==-1)return -2;
    for(int i=1;i<reg.size()-1;i++)
    {
        if(reg[i]=='^')return -3;

        if(reg[i]=='\\'){
                swap(reg[i],reg[i+1]);
                i++;
        }
          if(errorSymbols.find(reg[i]))
        {

            if(++numberOfSpeshalChar>2)return -4;
            if(reg.find(reg[i+1],1))return -5;
        }
    }
    return 0;
}
bool isContaint(string str, string reGex,int indexStr)
{
        for(int indexRegex = reGex.size();indexRegex>=0;indexRegex--)
        {
            if(indexStr<0 && indexRegex>0)return 0;
            switch(reGex[indexRegex])
            {
                case '^':
                    if(str[indexStr]==reGex[indexRegex])return 1;
                    else return 0;

                case '?':
                    if(str[indexStr]==reGex[--indexRegex])indexStr--;
                    indexRegex--;
                case '.':    break;
                case '+':
                    if(str[indexStr]==reGex[--indexRegex])indexStr--;
                     else return 0;
                case '*':
                    while(str[indexStr]==reGex[--indexRegex] && indexStr>=0)indexStr--;
                    indexRegex--;
                    break;
                case '\\':indexRegex--;
                default :
                    if(str[indexStr]==reGex[indexRegex])indexStr--;
                        else return 0;
                        break;
            }

        }
        return 1;

}
bool findRegex(string str,string reg)
{
    for(int i=str.size();i>=0;i--)
    {
        if(isContaint(str,reg,i))return 1;
    }
    return 0;
}
int fReadStr(string filename, string str, size_t line)
{

    ifstream MyFile(filename);
    if (!MyFile.is_open())return 1; // Unable to open file
    size_t lineNumber = 1;
    while ((lineNumber++ <= line) && (getline(MyFile,str)));
    if (MyFile.eof() && (line + 2 != lineNumber))
    return 2; // File is shorter than requested
    MyFile.close();
    return 0; // Success
}
int main()
{
    string regEx;
    string fileName;
    string str;
    getline(cin,regEx);
    getline(cin,fileName);
    int errorCode = normalize(regEx);
    if(errorCode!=0){
        cout<<errorCode;
        return 0;
    }
    int index =1;
 do
    {
        switch(fReadStr(fileName,str,index))
        {
            case 0:
            if(findRegex(str,regEx))cout<<str;
            index++;
            break;
            case 1:
                cout<<-2;
                return 0;
            case 2:return 0;
        }
       // cout<<str<<endl;

    }while(true);

return 0;

}
