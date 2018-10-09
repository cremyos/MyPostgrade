%%  
% �������������е�˼�룬��C++�����д��M�ļ�  
% http://www.cnblogs.com/zhangchaoyang/articles/2591663.html  
clear;clc;  
P=101;%ѵ��������P��  
X=[]; %ѵ������  
Y=[]; %ѵ�����  
M=10; %�������ĵĸ�������˵���ز�ĸ�����  
  
  
centers=[];%�洢�������ģ���˵�˺����ĸ�����  
deltas=[]; %�洢�˺����ı�׼��  
weights=[];%��������Ȩֵ����˵ÿ���˵�Ȩֵ��  
set = {};  %��Ų�ͬ������������������  
gap=0.1;   %������k_means�����о����ʱ���ֹͣ����  
%**************************************************************************  
%����ѵ������X,Y  
X=[-4:0.08:4];  
for i=1:P  
    Y(i)=1.1*(1-X(i)+2*X(i)^2)*exp(-X(i)^2/2);  
end  
Y=Y+0.1*randn(1,P);  
%%  
%**************************************************************************  
%��������о��࣬(��ú˺���������)  
for i=1:M   
    %��Ϊ���ǵ�X�Ǿ��ȷֲ�,���Գ�ʼ��ҲΪ���ȵ�  
    centers(i)= X( i*floor( P/10 ) );  
end  
done=0;  
while(~done)  
    for i=1:M  
       set{i}=[];  
    end  
    %����P��ÿ���������Ĵ�  
    for i=1:P  
        distance=100;%����һ���Ƚϴ��ֵ  
        for j=1:M  
            curr=abs(X(i)-centers(j));  
            if curr<distance  
                sets=j;  
                distance=curr;  
            end  
        end  
        set{sets}=[set{sets},X(i)];%���·������������Ӧ�Ĵ���  
    end  
    %���¼���ÿ���ص�����  
    for i=1:M  
        new_centers(i)=sum(set{i})/length(set{i});  
    end  
    %���ݸ������ĵĸ�����������Ƿ������ѭ��  
    done=0;  
%     abs(centers-new_centers)  
    for i=1:M  
        if abs(centers(i)-new_centers(i))>gap  
            done=0;  
            break;  
        else  
            done=1;  
        end  
    end  
    centers=new_centers;  
end  
%�����ÿ����˹�˺����ı�׼��ص�ϵ��=1��  
for i=1:M  
    curr=abs( centers-centers(i) );  
    [curr_2,b]=min(curr);  
    curr(b)=100;  
    curr_2=min(curr);  
    deltas(i)=1*curr_2;  
end  
%**************************************************************************  
%����d=sum(K*W)  
%���ȹ���KΪP��M��  
for i=1:P  
    for j=1:M  
        curr=abs(X(i)-centers(j));  
        K(i,j)=exp( -curr^2/(2*deltas(j)^2) );  
    end  
end  
%����Ȩֵ����  
weights=inv(K'*K)*K'*Y';  
%**************************************************************************  
%���Լ�������������  
x_test=[-4:0.1:4];  
for i=1:length(x_test)  
    sum=0;  
    for j=1:M  
        curr=weights(j)*exp(-abs(x_test(i)-centers(j))^2/(2*deltas(j)^2));  
        sum=sum+curr;  
    end  
    y_test(i)=sum;  
end  
figure(1)  
scatter(X,Y,'k+');  
hold on;  
plot(x_test,y_test,'r.-')