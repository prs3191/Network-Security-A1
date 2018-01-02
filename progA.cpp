/*to compile:
	 g++ u1076652_HW2_progA.cpp -o hw2_progA_obj
 to execute:
 	./hw2_progA_obj
 */

#include<iostream>
#include<string>
#include<cstring>
using namespace std;


unsigned static char state[256]={};
static int x=0,y=0;   
void build_state(char key[], int key_length) {
       
        int i;
        for (i=0;i<256;i++) state[i]=(char) (i);
       // for (i=0;i<256;i++) cout<<state[i]); 							/*Sotre 0-255 as character in state array*/
        //for (i=0;i<256;i++) cout<<state[i]+0 <<"\n";
        int j=0,k=0,temp=0;
       					   	   /*use all arithmetic operation using integer, swap and store values as character*/
        for (i=0;i<256;i++){
            temp=state[i]+0;
            j=(j+1)%key_length;
            k=(k+(key[j]+0)+temp)%256;
            state[i]=state[k];
            state[k]=(char)temp; 
            
        }
       //for (i=0;i<256;i++) cout<<state[i]+0<<"\n"; 				/*0-255 is shuffled now*/
         
    }

    static char generate_random() {
       
        char temp;
        y=((y)+(state[++x]+0))%256;
        x=x%256;
        temp=state[y];
        state[y]=state[x];
        state[x]=temp;
        
        return ( state[ ((state[x]+0)+(state[y]+0))%256 ] );
    }



int main(){

        // TODO code application logic here
        string s="",key="";
        int  key_len,s_len;
        char keystream;

		cout<<"\nEnter plain text:";
        getline(cin,s);
        s_len=s.length();
        //cout<<"\n"<<s<<"\n";
        //cout<<"\nLength P:"<<s_len;
                
		//unsigned char temp_input[s_len+1]={0};
		//unsigned char temp_output[s_len+1]={0}; 
		
		unsigned char temp_input[s_len+1];		/*s_len+1 because last char is a terminating char*/
		unsigned char temp_output[s_len+1]; 
		
		for(int i=0;i<s_len;i++){
			temp_input[i]=0;
			temp_output[i]=0;
		}
		
		temp_output[s_len]=0;
	  	//unsigned char sub_table[]={};sub_table[s_len]=0;
		for(int i=0;i<s_len;i++)
	 			temp_input[i]=s[i];
        temp_input[s_len]=0;					/*Terminate last char of array using NULL*/
		
	//	cout<<temp_input;
        cout<<"\nEnter key:";
		cin >> key;
  		//cout<<key<<"\n";
        key_len=key.length();
        //cout<<"\nLength K:"<<key_len;
        
		//char key_ch[key_len+1]={};
		char key_ch[key_len+1];
		
		for(int i=0;i<key_len;i++){
 				key_ch[i]=0;
		}
		
		for(int i=0;i<key_len;i++)
				key_ch[i]=key[i];
        key_ch[key_len]=0;

	//cout<<"\nLength K_ch:"<<key_len;
        build_state(key_ch, key_len);
		
  		cout<<"\n-------------ENCRYPTION------------------------\n";
  		cout<<"Input:\n"   ;         
            for(int i=0;i<s_len;i++){ 
                cout<<temp_input[i];cout<<" ";    
            }
            
            cout<<"\nKeystream:\n";
            for (int i=0;i<s_len;i++){
            	keystream=generate_random();								/*generate random key*/
            	cout<<keystream<<" "; 
                temp_output[i]= (char)((temp_input[i]+0) ^ (keystream+0));  /*xor input with generated keystream*/
                //cout<<"cipher text:"<<temp_output[i];cout<<"\n";
            }
           cout<<"\n";
        //output=temp_output;
        cout<<"\nCipher text is:"; cout<<temp_output<<"\n";
        
       
         /*decrypt*/
       cout<<"\n-------------DECRYPTION------------------------";

            build_state(key_ch, key_len);
            x=0;y=0;

            cout<<"\n";
            for (int i=0;i<s_len;i++){
            	keystream=generate_random();
                temp_output[i]= (char)((temp_output[i]+0) ^ (keystream+0));  /*xor cipher text with generated keystream*/
               // cout<<temp_input[i];cout<<" ";
            }
            cout<<"\nPlain text is:\n";
            cout<<temp_output<<"\n";
            
			return 0;
  
        }
        

         
        
  
   
 
    
