close all

p1 = 0:0.01:1;
p2 = 0:0.01:1;
[P1,P2] = meshgrid(p1,p2);
T = 0.8./exp(((P1-0.3).^2 + (P2-0.45).^2)/0.03)+0.3./exp(((P1-0.75).^2 + (P2-0.75).^2)/0.015)+0.6./exp(((P1-0.7).^2 + (P2-0.3).^2)/0.01);
surf(p1,p2,T);
%title('Training Vectors');
%xlabel('Input Vector P');
%ylabel('Target Vector T');
