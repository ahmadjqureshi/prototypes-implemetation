function a=img31(path,border) 
a = path; 

%if 1 == isrgb(a) | 1 == isgray(a)
%    a = im2bw(a);
%end
 
hw = size(a); 
height = hw(1); 
width = hw(2); 

found=0;
startx = 1; 
starty = 1; 
for y= 1:height 
   for x= 1:width 
      if  a(y,x) == border
         startx = x;
         starty = y;
         found=1;
      break; 
      end 
      if found == 1
          break;
      end
   end 
end 
found=0;
actualx = starty-1;
y=1;
x=1;

for t=1:width
for x= 1:height
    if a(x,y) == border
        startx = x;
        starty = y;
        found=1;
        break;
    end
    
    if x == height

        y=y+1;
    end
end
if found==1
        break;
    end
end
actualy = starty-1;
cropwidth = width-actualy;
cropheight = height-actualx;
found=0;
x=width;
y=height;
while x>1,
    x=x-1;
    y=height;    
   while y>1,
      y = y-1;
      if  a(y,x) == border 
         startx = x;
         starty = y;
         found=1;
      break; 
      end 
      if found == 1
          break;
      end
   end 
end 

cropwidth = cropwidth-(width - startx)+1;
found=0;
x=width;
y=height;
while y>1,
    y=y-1;
    x=width;    
   while x>1,
      x = x-1;
      if  a(y,x) == border 
         startx = x;
         starty = y;
         found=1;
      break; 
      end 
      if found == 1
          break;
      end
   end 
end 
cropheight = cropheight-(height - starty)+1;
t=width;
x=height;
found=0;
y=height;

a = imcrop(a,[actualy actualx cropwidth cropheight]);