#include <iostream>
#include <vector>
using namespace std;

struct XMLAttributes
{
    string AttributeName,AttributeValue;
    
};


struct XMLELEMENT
{
    string tag,innerValue;
    
    vector<XMLELEMENT*>tags;
    vector<XMLAttributes*>attributes;
    bool hasSons;
         

};
XMLELEMENT* xmlParser(string xmlstr,int& i );

void xmlAttributersParser(XMLELEMENT* xmlobject,string xmlstr,int& i);
int main(){


cout<<"test from xml parser\n";


    string type="<xmlExample fAtt=\"dfv\" secAtt=\"vcvvc\">dfdf</xmlExample>";
    int starter=0;
auto xmlElement=xmlParser(type, starter );
    return 0;
}
XMLELEMENT* xmlParser(string xmlstr,int& i ){

    while (i<xmlstr.length())
    {
        if (xmlstr[i]=='<')
        {
            break;
        }
        ++i;
    }
//now moving to the name of the tag index start
++i;

    string TagName="";

    while (i<xmlstr.length())
    {
        if (xmlstr[i]=='>'||xmlstr[i]==' '||xmlstr[i]=='/')
        {
            break;
        }
        TagName+=xmlstr[i];
        ++i;
    }
    //moving to the next probable whitespace
    
    ++i;

    XMLELEMENT* element= new XMLELEMENT();
    element->tag=TagName;

 while (i<xmlstr.length())
    {
        if (xmlstr[i]!='>'||xmlstr[i]!=' '||xmlstr[i]!='/')
        {
            xmlAttributersParser(element,xmlstr,i);
            //if true this means the tag has no sons
            
            
            if (xmlstr[i]=='>')
            {
                if (xmlstr[i-1]=='/')
            {
                element->hasSons=false;
            }else{
                element->hasSons=true;
              
            }
            ++i;

 while (xmlstr[i]!='<')
               {
                   element->innerValue+=xmlstr[i];
                   ++i;
               }
               //getting near to check if its the closing tag
            ++i;
            ++i;
            int j=0;
            string toCompare="";
                while (j<element->tag.length())
                {
                    toCompare+=xmlstr[i];
                    ++j;
                    ++i;
                }

                if (toCompare==element->tag)
                {
                element->hasSons=false;    
                }
                --i;
                --i;
                i-=element->tag.length();
                
                

            }
            
           
            
            break;
        }
    
        ++i;
    }
    
if (!element->hasSons)
{
    return element;
}


xmlAttributersParser(element,xmlstr,i);
    


}
void  xmlAttributersParser(XMLELEMENT* xmlobject,string xmlstr,int& i)


{
//"<xmlExample fAtt=\"dfv\" secAtt=\"vcvvc\"/>";

int inParenthesses=0;
string AttributeName="";
string AttributeValue="";



 while (i<xmlstr.length())
    {
           
         if (inParenthesses>0&&(xmlstr[i]=='\"'||xmlstr[i]=='/'||xmlstr[i]=='>'))
        {
                  AttributeValue+=xmlstr[i];
             inParenthesses--;
                XMLAttributes* attribute= new XMLAttributes();
             attribute->AttributeName=AttributeName;
          
            for(int index=1;index<AttributeValue.length();++index){
                
                    if (AttributeValue[index]=='\"')
                    {
                        break;
                    }
                    

                attribute->AttributeValue+=AttributeValue[index];
            }
           
             xmlobject->attributes.push_back(attribute);
             AttributeValue="";
             AttributeName="";
              ++i;

        }
        if (inParenthesses<1&&xmlstr[i]=='\"')
        {
            inParenthesses++;

        }
        

    
        if (inParenthesses<1)
        {
             if (xmlstr[i]=='/'||xmlstr[i]=='>')
        {

         break;

        }
        
          if (xmlstr[i]!='='&&xmlstr[i]!=' ')
        {
         AttributeName+=xmlstr[i];

        }
         
        
    
        }else{
               AttributeValue+=xmlstr[i];
        }
        
     
        

            // inParenthesses--;
            // attribute->AttributeName=AttributeName;
            // attribute->AttributeValue=AttributeValue;
            // attributes.push_back(attribute);
            // AttributeName="";
            // AttributeValue="";
        

        
     
            
        

        

        


    
        ++i;
      
    }



    cout<<'\n'<<xmlstr[i];

}
