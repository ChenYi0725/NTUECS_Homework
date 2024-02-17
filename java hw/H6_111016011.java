import java.util.*;//d、f
/*
  作者:資二甲 陳奕 111016011
  操作說明:重複輸入一個數字，系統會將其累加並輸出，當輸出q時則會中止輸入
  自評:100 功能皆有達成
  額外功能:可重複使用
 */
public class H6_111016011{
	public static void main(String args[]){
		Scanner scan=new Scanner(System.in);
		String re;									//重複使用	
		String input="0";							//輸入字串
		float num=0,total=0;						//抓住輸入轉浮點數，五個數加總的值

		while(true){
			num=0;													//將上次使用的變數設回初始值
			total=0;
			for(int i=1;i<6;i++){									//重複輸入五個數字
				System.out.println("請輸入第 "+i+" 個數字");	
				input=scan.nextLine();								//輸入
				if(input.contains("q")&&input.length()==1){			//輸入q結束程式
					break;									
				}
				
				if(input.contains("d")||input.contains("f")){		//若輸入的最後一個字元為d或f時不會跳出例外，所以加一個判斷式阻擋
					System.out.println("輸入錯誤，請重新輸入一個數字");	
					i--;											//讓這次輸入不計數
					continue;
				}
				
				try{
					num=Float.valueOf(input);						//String 轉float
						
				}catch(Exception e){
					System.out.println("輸入錯誤，請重新輸入一個數字");	
					i--;											//讓這次輸入不計數
					continue;
				}
				total=total+num;									//加總輸入的值
				
			}
			
			System.out.println("總合為："+total);
//----------------------------重複使用			
			System.out.println("\n是否再使用一次(輸入1繼續，輸入0退出)");	//重新輸入迴圈
			re=scan.nextLine();
			while(!(re.contains("1")||re.contains("0"))||re.length()!=1){						//檢查是否為1或0
				System.out.println("請重新輸入(輸入1繼續，輸入0退出)");
				re=scan.nextLine();
				if((re.contains("1")||re.contains("0"))&&re.length()==1){
					break;
				}				
			}
			if(re.contains("0")){			//0直接結束
				break;
			}
//----------------------------重複使用			
			
		}
		System.out.println("感謝您的使用");	

	}
}