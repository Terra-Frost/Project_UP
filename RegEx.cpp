#include  <iostream>
#include  <cstdlib>
#include  <fstream>
using  namespace  std;
int normalize(string& reg)
{
    const string errorSymbols = "\\^.*+?";
    int numberOfSpeshalChar=0;

    if(reg[reg.size()-1]=='\\')return -1;
    //cout<< reg[0]<<  " "<<errorSymbols.find(reg[0])<<" "<<std::npos<<endl;
    if(errorSymbols.find(reg[0],3)!=string::npos)return -2;
    for(int i=0;i<reg.size();i++)
    {
        if(reg[i]=='\\'){

                if(errorSymbols.find(reg[i+1])==string::npos)return -3;
                    swap(reg[i],reg[i+1]);
                    i++;

        }
        else{
            int specialSymbol = errorSymbols.find(reg[i],1);
            if(specialSymbol!=-1)
            {
                if(specialSymbol>2 && ++numberOfSpeshalChar>=2) return -4;
                if(errorSymbols.find(reg[i+1],3)!=string::npos)return -5;
            }
        }

        if(reg[i]=='^' && i!=0)return -6;

    }
    return 0;
}
bool isContaint(string str, string reGex,int indexStr)
{
        for(int indexRegex = reGex.size()-1;indexRegex>=0;indexRegex--)
        {
           // cout<<indexRegex<<endl;
           //cout<<str[indexStr]<<"->"<<(int)str[indexStr]<<" "<<reGex[indexRegex]<<"->"<<(int)reGex[indexRegex]<<" "<<reGex[indexRegex-1]<<"->"<<(int)reGex[indexRegex-1]<<endl;
            if(indexStr<0)return 0;
            switch(reGex[indexRegex])
            {
                case '^':
                    if(str[indexStr]=='\n')return 1;
                    else return 0;
                    break;
                case '?':
                    if(str[indexStr]==reGex[--indexRegex])indexStr--;
                    break;
                case '.':
                    indexStr--;
                    break;
                case '+':
                    if(str[indexStr]==reGex[indexRegex-1])indexStr--;
                     else return 0;
                case '*':
                    indexRegex--;
                    while(str[indexStr]==reGex[indexRegex] && indexStr>=0)indexStr--;
                    break;
                case '\\':indexRegex--;
                default :
                    if(str[indexStr]==reGex[indexRegex])indexStr--;
                        else return 0;
                        break;
            }

        }
        //cout<<"q";
        return 1;

}
bool findRegex(string str,string reg)
{
   // cout<<str<<endl;
    str='\n'+str;

    for(int i=str.size()-1;i>=0;i--)
    {
        //cout<<i<<endl;

        if(isContaint(str,reg,i))return 1;
       // cout<<endl;
    }
   // cout<<endl;
    return 0;
}
int fReadStr(string filename, string& str, size_t line)
{
        //cout<<" -------"<<endl;
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

            if(findRegex(str,regEx))cout<<str<<endl;
            index++;
            break;
            case 1:
                cout<<1;
                return 0;
            case 2:return 0;
        }
       // cout<<str<<endl;

    }while(true);

return 0;

}
