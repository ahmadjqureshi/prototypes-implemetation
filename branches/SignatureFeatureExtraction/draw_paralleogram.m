function no_of_end_points=draw_paralleogram(image)

a = imread(image);
if (isrgb(a))
    a = rgb2gray(a);
end
a = im2bw(a);
hw = size(a); 
height = hw(1); 
width = hw(2); 

highestx=0;
highesty=0;
leftmostx=0;
leftmosty=0;
lowestx=0;
lowesty=0;
rightmostx=0;
rightmosty=0;


found=0;
startx = 1; 
starty = 1; 

for x=1:width
    for y=1:height
        if a(y,x) == 0
            leftmostx=x;
            leftmosty=y;
            found =1;
            break;
        end
    end
    if found == 1
        break;
    end
end
            
found =0;

for y= 1:height 
   for x= 1:width 
      if  a(y,x) == 0 
          highestx = x;
          highesty = y;
          found=1;
          break; 
      end 
      if found == 1
          break;
      end
   end 
end 

found =0;

temp_y = height;
while temp_y >= 1
    for x=1:width
        if a(temp_y,x) == 0
            lowestx = x;
            lowesty = temp_y;
            found =1;
            break;
        end
    end
    if found == 1
        break;
    end
    temp_y = temp_y -1;
end

found =0;
temp_x = width;

while temp_x >= 1
    for y=1:height
        if a(y,temp_x) == 0
            rightmostx = temp_x;
            rightmosty = y;
            found =1;
            break;
        end
    end
    if found == 1
        break;
    end
    temp_x = temp_x -1;
end
no_of_end_points=4;


%
if  ((rightmostx == lowestx)||(rightmostx == lowestx-1)||(rightmostx == lowestx-2)||(rightmostx == lowestx+1)||(rightmostx == lowestx+2)||(rightmostx == lowestx-3)||(rightmostx == lowestx-3)) && rightmosty == lowesty
    no_of_end_points=no_of_end_points - 1;
end
%
if  ((rightmostx == highestx)||(rightmostx == highestx-3)||(rightmostx == highestx+3)||(rightmostx == highestx-1)||(rightmostx == highestx-2)||(rightmostx == highestx+1)||(rightmostx == highestx+2)) &&rightmosty == highesty
    no_of_end_points = no_of_end_points-1;
end
%
if  ((leftmostx == highestx)||(leftmostx == highestx-3)||(leftmostx == highestx+3)||(leftmostx == highestx-1)||(leftmostx == highestx-2)||(leftmostx == highestx+1)||(leftmostx == highestx+2)) &&leftmosty == highesty
    no_of_end_points = no_of_end_points - 1;
end
%
if  ((leftmostx == lowestx-2)||(leftmostx == lowestx-3)||(leftmostx == lowestx+3)||(leftmostx == lowestx-1)||(leftmostx == lowestx)||(leftmostx == lowestx+1)||(leftmostx == lowestx+2)) && leftmosty == lowesty
    no_of_end_points = no_of_end_points-1;
end

%Calculate Horizontal angle between lowest and right most point

xdiff = rightmostx - lowestx;
ydiff = lowesty - rightmosty;

div = ydiff/xdiff;

first_hori_angle = (atan(div))*(180/3.14);

%Calculate Horizontal angle between lowest and left most point

xdiff = lowestx - leftmostx;
ydiff = lowesty - leftmosty;

div = ydiff/xdiff;

sec_hori_angle = (atan(div))*(180/3.14);

%Calculate Horizontal angle between left most point and top most point

xdiff = highestx - leftmostx;
ydiff = leftmosty - highesty;

div = ydiff/xdiff;

third_hori_angle = (atan(div))*(180/3.14);

%Calculate Horizontal angle between top most point and right most point

xdiff = rightmostx - highestx;
ydiff = rightmosty - highesty;

div = ydiff/xdiff;

fourth_hori_angle = (atan(div))*(180/3.14);

array(1,1) = first_hori_angle;
array(2,1) = sec_hori_angle;
