void float2str(char * buf,float fnum,int intbit,int floatbit){
	float f = fnum;
	int i = 0;
	for(i=0;i<floatbit;i++){
		f *= 10;
	}
	char arr[floatbit+intbit+1];//1 for dot
	int num = (int)f;
	int j = 0;
	while(num!=0){
		arr[j] = num%10 + '0';
		num /= 10;
		j++;
	}
	while(j<floatbit+intbit){
		arr[j] = '0';
		j++;
	}
	j = j-1;
	i = 0;
	while(j>=floatbit){
		buf[i] = arr[j];
		i++;j--;
	}
	buf[i] = '.'; i++;
	while(j>=0){
		buf[i] = arr[j];
		i++;j--;
	}
}