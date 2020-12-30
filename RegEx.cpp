#include  <iostream>
#include  <cstdlib>

using  namespace  std;
void normalize(string& reg)
{
    for(int i=0;i<reg.size();i++)
    {
        if(reg[i]=='\\')swap(reg[i],reg[i+1]);
    }
}
bool isContaint(string str, string reGex,int indexStr)
{
        for(int indexRegex = reGex.size();indexRegex>=0;indexRegex--)
        {
            if(indexStr<0 && indexRegex>0)return 0;
            switch(reGex[indexRegex])
            {
                case '.':break;
                case '?':
                    if(str[indexStr]==reGex[--indexRegex])indexStr--;
                    indexRegex--;
                    break;
                case '*':
                    while(str[indexStr]==reGex[--indexRegex] && indexStr>=0)indexStr--;
                    indexRegex--;
                    break;
                case '+':
                    if(str[indexStr]==reGex[--indexRegex])indexStr--;
                     else return 0;
                    while(str[indexStr]==reGex[--indexRegex] && indexStr>=0)indexStr--;
                    indexRegex--;
                    break;
                case '\\':indexRegex--;
                default :
                    if(str[indexStr]==reGex[indexRegex])indexStr--;
                        else return 0;
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
int main()

{

 string str = "aaaaaaaaaaa";
 string reg = "a+";
 //normalize(reg);
 cout<<findRegex(str,reg);

return 0;

}
