/*
to compile:
	 g++ u1076652_HW2_progB.cpp -o hw2_progB_obj
to execute:
 	./hw2_progB_obj
*/

/*Using bytes generated from RC4 as a substitution table
Encryption:
		   1. Get 8 byte input/plaintext from user
		   2. Get 8 byte key from user
		   3. Build initial state table using RC4
		   4. XOR input with key given by user (byte by byte) and store it in array I2
		   5. Store random bytes generated in array 'SUB' of length same as input
		   6. XOR SUB with I2 (byte by byte) and store it in SUB
		   7. Substitute I2 with SUB (byte by byte)
		   8. Permute by left circular shift on each char in I2
		   9. Print output for the round.
          10. Continue steps from 5-9 for 16 times
Decryption:
		   1. Get Cipher text from last round of encryption. Let it be I2.
		   	  Round i for decryption starts below
		   2. Build initial state table using RC4
		   3. Store random bytes generated in array 'SUB' of length same as input 
		   	  and find SUB for rounds+1-i . Here rounds=16
           4. Permute by right circular shift on each char in I2
		   5. XOR SUB with I2 (byte by byte) and store it in SUB. By commutative property of XOR.
		   6. Substitute I2 with SUB (byte by byte)
		   7. Print decrypted text for Round i
		   8. Continue steps from 2-7 for 16 times
		   9. XOR output (after 16 rounds) with key given by user (byte by byte) and print the decypted text (By commutative property of XOR.)
*/


#include<iostream>
#include<string>
using namespace std;

	
 unsigned static char state[256]={};
 static int x=0,y=0;   
void build_state(char key[], int key_length) {
       
        int i;
        for (i=0;i<256;i++) state[i]=(char) (i);
       // for (i=0;i<256;i++) cout<<state[i]); 			/*Sotre 0-255 as character in state array*/
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
       // for (i=0;i<256;i++) cout<<state[i]+0<<"\n"; 	/*0-255 is shuffled now*/
         
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
        int  ip_len;
        	
        do{
		
       	cout<<"\nEnter plain text:";
        getline(cin,s);
        s_len=s.length();
        ip_len=s_len;
        if (s_len>8 || s_len <=0 ) cout <<"\nPlease enter plain text of 8 bytes..\n";
    	} while (s_len>8 || s_len <=0 );
                   
		unsigned char temp_input[s_len+1];
		unsigned char temp_output[s_len+1];
		unsigned char sub_table[s_len+1];
		
		for(int i=0;i<s_len;i++){
			temp_input[i]=0;
			temp_output[i]=0;
			sub_table[i]=0;
		}
		
		
		temp_output[s_len]=0;
		sub_table[s_len]=0;
		
		for(int i=0;i<s_len;i++)
				temp_input[i]=s[i];
        temp_input[s_len]=0;
        
        cout<<"\nEnter key:";
		cin >> key;
        key_len=key.length();
		char key_ch[key_len+1];
		for(int i=0;i<key_len;i++){
 				key_ch[i]=0;
		}
		for(int i=0;i<key_len;i++)
				key_ch[i]=key[i];
        key_ch[key_len]=0;

        build_state(key_ch, key_len);
        cout<<"\n-------------ENCRYPTION------------------------\n";
        for(int i=0;i<ip_len;i++){
            temp_output[i]= (char)((temp_input[i]+0)^(key_ch[i]+0));
        }
        for(int f=1;f<17;f++){
    //        cout<<"b4 subs..\n";
            for(int i=0;i<ip_len;i++){
                sub_table[i]=generate_random();
    //             cout<<sub_table[i];cout<<" ";
            }
    //        cout<<"\n";
    //        cout<<"x="<<x<<"\n";
    //        cout<<"Substitution Table:\n";
            for(int i=0;i<ip_len;i++){ 
    //            cout<<temp_output[i];cout<<" ";    
            }
    //        cout<<"\n";
            for (int i=0;i<ip_len;i++){
                sub_table[i]= (char)((temp_output[i]+0) ^ (sub_table[i]+0)); /*substitue*/
    //            cout<<sub_table[i];cout<<" ";
            }
    //        cout<<"\n";
            for(int i=0;i<ip_len;i++){
                
                temp_output[i]= sub_table[i]; /*substitue*/
    //             cout<<"tempout["<<i<<"]=";cout<<temp_output[i]+0<<"\n";
                temp_output[i]= (char)((temp_output[i]+0) << 1 | (temp_output[i]+0) >> 7); /*permutation by left circular shift of bits*/

    //           cout<<"tempout["<<i<<"]=";cout<<temp_output[i]+0<<"\n";
            }
            cout<<"\nRound "<<f<<" output:"; cout<<temp_output<<"\n";
    //        cout<<"-------------------------------------------\n";
        }
        //output=temp_output;
        cout<<"\nCipher text is:"; cout<<temp_output<<"\n";
        
        
         /*decrypt*/
       cout<<"\n-------------DECRYPTION------------------------\n";
       int round=17;
         for(int f=1;f<round;f++){
            build_state(key_ch, key_len);
            x=0;
            y=0;
    //        cout<<"b4 subs.."<<"\n";
            
               for(int ii=round-f;ii>0;ii--){
                   for(int jj=0;jj<ip_len;jj++){
                    sub_table[jj]=generate_random(); 
                   }
               }
               for(int i=0;i<ip_len;i++){
    //           cout<<sub_table[i];cout<<" ";
               }
               
            
    //         cout<<"\n";
    //         cout<<"x="<<x<<"\n";
            for(int i=0;i<ip_len;i++){
                
    //            cout<<"tempout["<<i<<"]=";cout<<temp_output[i]+0;
                temp_output[i]= (char)(((temp_output[i]+0) >> 1) | ((temp_output[i]+0) << 7)); /*permutation by right circular shift of bits*/

    //            cout<<"tempout["<<i<<"]=";cout<<temp_output[i]+0;
                
            }
    //       cout<<"\nSubstitution Table:\n";
            for(int i=0;i<ip_len;i++){ 
    //            cout<<temp_output[i];cout<<" ";    
            }
    //        cout<<"\n";
            for (int i=0;i<ip_len;i++){
                sub_table[i]= (char)((temp_output[i]+0) ^ (sub_table[i]+0)); /*substitue*/
    //            cout<<sub_table[i];cout<<" ";
            }
    //        cout<<"\n";
             for(int i=0;i<ip_len;i++){
                   temp_output[i]=sub_table[i]; /*substitue*/
            }
    //        cout<<"\n";
            cout<<"\nRound "<<f<<" output:"; cout<<temp_output<<"\n";
    //        cout<<"-------------------------------------------";
        }
        //output=temp_output;
    //    cout<<"Plain text is:\n";
        for(int i=0;i<ip_len;i++){
            temp_output[i]= (char)((temp_output[i]+0)^(key_ch[i]+0));
    //         cout<<temp_output[i];
        }
        cout<<"\nPlain text is:"; cout<<temp_output<<"\n";
         
        
        return 0;
    }
    
   
 
    
