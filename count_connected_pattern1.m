function c=count_connected_pattern1(img)
a = imread(img);

if isgray(a) == 0
%    a = im2bw(a,0.8);
    a = rgb2gray(a);
end


hw = size(a);
b =uint16(a);

%b=a;

height = hw(1);
width = hw(2); 
i=1000;
for x=1:width
    for y=1:height
        if  b(y,x) < 220
            b = mark1(b,i,x,y);
            i=i+1;
        end
    end
end
L=1000;

no_of_connected_patterns=0;
gray_area=0;
total_area=0;
dp_gray=0;
dp_nomalized=0;
index=3;
for L=1000:i
       tempimg=img31(b,L);
       temphw=size(tempimg);
       tempheight=temphw(1);
       tempwidth= temphw(2);
       dp_gray=0;
       if tempheight <15 && tempwidth<15
       else
           for y=1:tempheight
               for x=1:tempwidth
                   if tempimg(y,x)==L
                       gray_area=gray_area+1;
                       dp_gray = dp_gray + 1;
                   end
               end
           end
           total_area=total_area+(tempheight*tempwidth);    
           no_of_connected_patterns=no_of_connected_patterns+1;
           c(index,1)=dp_gray/(tempheight*tempwidth);
           index=index+1;
       end
end
c(1,1) = no_of_connected_patterns;
c(2,1) = gray_area/total_area;