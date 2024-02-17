import java.util.Scanner;
/*
 作者:資二甲 陳奕 111016011
 操作說明:輸入多個整數，中間以空格分開，會將這些整數以小到大排列
 自評:100 功能皆有達成、能正確運作且能辨別輸入是否為整數，排列的方法有參考課本6-3
 額外功能:可重新輸入，且能分辨重新輸入是否為1、0或是其他輸入
 */

public class H2_111016011{
	public static void main(String[] args) {
			Scanner scan = new Scanner(System.in);
			boolean checkint=true;	//確認input是否為整數的布林值
			String re;					//重複使用
			int min;
			int max;
			int point;
			while(true){
				while(checkint){
					checkint=false;
					System.out.println("請輸入多個整數(中間用1個空格隔開)");
					
					String[] input= scan.nextLine().split(" "); //輸入並以空格分割字串									
					int num[]=new int[input.length];			
					int output[]=new int[input.length];					
					for(int i=0;i<input.length;i++){				//將字串陣列依序轉成整數陣列，並檢查有無錯誤
						try{
							num[i] = Integer.parseInt(String.valueOf(input[i]));
							
						}catch(Exception e){		//若輸入錯誤
							System.out.println("輸入錯誤，請重新輸入");
							checkint=true;
							break;
						}
					}
					
					if(!checkint){										//如果數字串正確則排序並輸出，若不正確則跳過此步驟並重新輸入
						for(int i=0;i<input.length;i++){				//將分割出的字串以int存入num
							num[i] = Integer.parseInt(String.valueOf(input[i]));	
						}
						min=num[0];	
	//------------------------------------------大小排序
						for(int i=0;i<num.length;i++){		//找出最小值min		
							if(min>num[i]){					
							min=num[i];
							}
						}
						
						for(int j=0;j<num.length;j++){			//陣列排序，先找最大的然後依序放在output後面
							max=min;
							point=0;
							for(int i=0;i<num.length;i++){		//找出最大值，並把point定為最大值位置
								if(max<num[i]){					
									max=num[i];
									point=i;
								}
								
							}	
							num[point]=min-1;							//把找到的最大值換成最小值-1
							output[output.length-1-j]=max;				//把最大值從右邊往左放
														
						}
	//-------------------------------------------大小排序
						for(int i=0;i<output.length;i++){			//輸出
							System.out.print(output[i]+" ");
						}
						
						System.out.print("\n");							
					}
	
				}

				checkint=true;				
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
	}
}

