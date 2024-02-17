import java.util.Scanner;
public class H1_111016011
{
	public static void main(String args[])
	{
		Scanner scn=new Scanner(System.in);
		int input;
		int limit;
		boolean check=false;

		System.out.println("enter an integer:");
		input=scn.nextInt();						//輸入input
		limit=(int)Math.floor(Math.sqrt(input));	//取得input的平方根	
		if(input==0||input==1){								//if input是0 or 1
			System.out.println(input+"neither");	
		}else if(input<0){									//input為負數
			System.out.println("not neg");
		}else{										//判斷input是不是質數
			if(input%2==0){				//input is even
				check=true;
			}else{						//input is odd
				for(int i=3;i<=limit;i=i+2){					//從3開始找input可被哪個數整除
					if(input%i==0){							//檢查input是否能被i整除
						check=true;
						break;
					}
				}				
			}			
		}
		if(check){
			System.out.println("no");
			System.out.println("decetegrade:");
			while(check){
				check=false;
				if(input%2==0){				//input is even
					check=true;
					input=input/2;
					
					System.out.print("2");
					if(input!=1){
						System.out.print("*");			//持續在每個數字後面輸出*直到input被整除
					}
				}else{						//input is odd
					for(int i=3;i<=input;i=i+2){					//從3開始找input可被哪個數整除
						if(input%i==0){							//檢查input是否能被i整除
							input=input/i;
							check=true;	
							System.out.print(i);
							if(input!=1){
								System.out.print("*");			//持續在每個數字後面輸出*直到input被整除
							}
							break;
						}
					}				
				}	
			}
			System.out.print("\n");

		}else{
			System.out.println("yes");	//質數
		}
			
	}
}