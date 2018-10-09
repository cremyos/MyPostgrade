function correct_rate=Batch_RBF_Neural_Network(train_data,test_data,hidden_layers,Wkj,c,sigma,theta,eta)
%-------------------------------------------------------------------
%Batch RBF neural network function with only one output neutron
%Inputs:
%train_data     -train data(including samples and its target output)
%test_data      -test data(including samples and its target output)
%hidden_layers  -numbers of hidden layers
%Wkj            -weights between hidden layer and putput layer
%c              -array of center points
%sigma          -standard deviation of Gaussian function
%theta          -threhold of delta target function
%eta            -learnning rate
%Output:
%correct_rate:  -classification correct rate of the test data
%-------------------------------------------------------------------
[rows,cols]=size(train_data);
train_input=train_data(1:rows-1,:);
train_target=train_data(rows,:);
test_input=test_data(1:rows-1,:);
test_target=test_data(rows,:);
%batch rbf algorithm
r=0;   %initialize the episode
J=zeros(1,1000); %initialize the error function
while(1)     %outer loop
    r=r+1;m=0;DELTA_Wkj=zeros(1,hidden_layers);DELTA_c=zeros(hidden_layers,size(train_input,1));  
    DELTA_sigma=zeros(1,hidden_layers);%initialization
    while(1)    %inner loop
        m=m+1; 
        yj=zeros(1,hidden_layers);
        for j=1:hidden_layers
            %calculate the output of the hidden layer
            yj(1,j)=exp(-sum((train_input(:,m)'-c(j,:)).*(train_input(:,m)'-c(j,:)))/(2*sigma(1,j)^2));  
        end
        zk=sum(yj(1,:).*Wkj(1,:));  %output of the output layer
        error=train_target(1,m)-zk;
        J(1,r)=J(1,r)+error^2/2;   %accumulate every error
        for j=1:hidden_layers
            %update the DELTA_Wkj,DELTA_c and DELTA_sigma
            DELTA_Wkj(1,j)=DELTA_Wkj(1,j)+eta*error*yj(1,j);  
            DELTA_c(j,:)=DELTA_c(j,:)+eta*error*Wkj(1,j)*yj(1,j)*(train_input(:,m)'-c(j,:))/sigma(1,j)^2;
            DELTA_sigma(1,j)=DELTA_sigma(1,j)+eta*error*Wkj(1,j)*yj(1,j)* ...
            sum((train_input(:,m)'-c(j,:)).*(train_input(:,m)'-c(j,:)))/sigma(1,j)^3;
        end
        if(m==cols)  %all samples has been trained(one episode)
            break;   %back to outer loop
        end
    end    %end inner loop
    for j=1:hidden_layers
        Wkj(1,j)=Wkj(1,j)+DELTA_Wkj(1,j);   %update Wkj
        c(j,:)=c(j,:)+DELTA_c(j,:);   %update c
        sigma(1,j)=sigma(1,j)+DELTA_sigma(1,j);  %update sigma
    end
    J(1,r)=J(1,r)/cols;
    if((r>=2)&&abs(J(1,r)-J(1,r-1))<theta)  %determine when to stop
        %disp('ok!');disp(r);
        %plot(0:r-1,J(1,1:r));hold on;

        %start to test the model 
        correct=0;
        for i=1:size(test_input,2)
            test_yj=zeros(1,hidden_layers);
            for j=1:hidden_layers
                test_yj(1,j)=exp(-sum((test_input(:,i)'-c(j,:)).*(test_input(:,i)'-c(j,:)))/(2*sigma(1,j)^2));
            end
            test_zk=sum(test_yj(1,:).*Wkj(1,:));  
            if((test_zk>0&&test_target(1,i)==1)||(test_zk<0&&test_target(1,i)==-1))
                correct=correct+1;
            end
        end
        correct_rate=correct/size(test_data,2);
        break;
    end
end
