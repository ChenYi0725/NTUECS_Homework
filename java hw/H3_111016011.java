import java.util.Scanner;
/*
  作者:資二甲 陳奕 111016011
  操作說明:會產生一組由4個不重複數字組成的數字串，使用者可輸入相同格式的數字串，每次輸入完成系統都會告知結果，
  		   (A:猜對數值及位置 B:猜對數值但位置有錯), 直到猜提者猜對為止,並告知共猜了多少次, 若超過10次,則顯示答
  		   案並結束程式
  自評:100 功能皆有達成、能正確運作、能判別輸入是否正確，且能重複執行1
  額外功能:可重新輸入，且能判斷輸入是否正確
 */
public class H3_111016011{
	public static void main(String args[]){
		Scanner scan = new Scanner(System.in);
		String re;					//重複使用
		int ans[];
		int a=0;
		int b=0;
		boolean anscorrect;			//是否答對
		boolean inputincorrect=false;		//是否輸入正確
		while(true){
			anscorrect=false;
			ans=new int[4];
			for(int i=0;i<ans.length;i++){			//產生題目(0~9的不重複數字)
				ans[i]=(int)(Math.random()*10);
				for(int j=0;j<i;j++){		//若重複則重新產生
					if(ans[i]==ans[j]){
						i--;
					}
				}
			}		
			
			System.out.print("ans:");				//觀察用
			for(int i=0;i<ans.length;i++){
				System.out.print(ans[i]);
			}		
			System.out.print("\n");		
	//-------------------輸入		
			for(int t=0;t<10;t++){										//猜題10次
				System.out.print("請輸入4位數字: ");
				String[] guess = scan.nextLine().split("");	 //輸入字串+把字串內每個數字分割		
				if(guess.length!=4){						//若輸入超過4個數字
						inputincorrect=true;
					}
							
				int num[]=new int[4];
				
				
				for(int i=0;i<guess.length;i++){			//把字串內每個數字取出
					try{
						num[i] = Integer.parseInt(String.valueOf(guess[i]));
					}catch(Exception e){
						inputincorrect=true;
						break;
					}				
				}
				for(int l=0;l<3;l++){				//比對有無重複數字14 13 12 24 23 34
					for(int r=3;r>l;r--){
						if(num[r]==num[l]){
							inputincorrect=true;
						}
					}
				}
				if(inputincorrect){							//如果輸入錯誤則提示
					System.out.println("輸入錯誤，正確格式為不重複4個數字");
					System.out.println("example:0123");
				}
				
				while(inputincorrect){							//如果輸入錯誤則重新輸入
					inputincorrect=false;
					System.out.print("請輸入4位數字: ");
					guess = scan.nextLine().split("");	 	//輸入字串+把字串內每個數字分割		
					if(guess.length!=4){					//若輸入超過4個數字
							inputincorrect=true;
						}				
					for(int i=0;i<guess.length;i++){		//把輸入的字串陣列轉成整數
						try{
							num[i] = Integer.parseInt(String.valueOf(guess[i]));
						}catch(Exception e){
							inputincorrect=true;
							break;
						}
					}
					for(int l=0;l<3;l++){				//比對有無重複數字14 13 12 24 23 34
						for(int r=3;r>l;r--){
							if(num[r]==num[l]){	
								inputincorrect=true;
							}
						}
					}
					if(inputincorrect){							//如果輸入錯誤則提示
						System.out.println("輸入錯誤，正確格式為不重複4個數字");
						System.out.println("example:0123");
					}
				}	
	//-------------------輸入			
	//-------------------判斷幾A幾B	
				for(int i=0;i<guess.length;i++){		//從num頭跑到尾
					for(int j=0;j<ans.length;j++){					//從ans頭跑到尾
						if(num[i]==ans[j]){							//如果有相同則B+1且檢查位置是否相同
							b++;
							if(i==j){
								b--;
								a++;
							}
						}	
					}
				}
				if(a==4){				//如果答對
					anscorrect=true;
					System.out.print("恭喜答對，答案為");
					a=0;										//重置AB
					b=0;
					for(int i=0;i<ans.length;i++){
						System.out.print(ans[i]);
					}		
					System.out.print("\n");
						break;
				}
	//-------------------判斷幾A幾B		
	//-------------------輸出	
				System.out.println(a+"A"+b+"B\t剩下"+(9-t)+"次機會");
				a=0;										//重置AB
				b=0;
			}
			
			if(!anscorrect){				//若答題次數用盡且沒猜到正確答案
				System.out.print("猜題次數用盡，答案為");
				a=0;										//重置AB
				b=0;
				for(int i=0;i<ans.length;i++){
					System.out.print(ans[i]);
				}		
				System.out.print("\n");			
			}
	//-------------------輸出
			System.out.println("是否再使用一次(輸入1繼續，輸入0退出)");	//重新輸入迴圈
			re=scan.nextLine();
			
			while(!(re.contains("1")||re.contains("0"))||re.length()!=1){						//檢查是否為1或0
				System.out.println("請重新輸入");
				re=scan.nextLine();
				if((re.contains("1")||re.contains("0"))&&re.length()==1){
					break;
				}				
			}
			
			if(re.contains("0")){			//0直接結束
				break;
			}
		}
		System.out.println("感謝您的使用");			
	}
}