function a=mark1(a,val,x,y)
hw = size(a);
height = hw(1); 
width = hw(2);
a(y,x) = val;
if x+1 <= width 
    if a(y,x+1) < 220
        a = mark1(a,val,x+1,y);
    end
end
if y+1 <= height 
    if a(y+1,x) < 220
        a = mark1(a,val,x,y+1);
    end
end
if y-1 >= 1 
    if a(y-1,x) < 220
        a = mark1(a,val,x,y-1);
    end
end
if x+1 <= width && y+1 <= height 
    if a(y+1,x+1) < 220
        a = mark1(a,val,x+1,y+1);
    end
end
if x-1 >= 1 && y-1 >= 1
    if a(y-1,x-1) < 220
        a = mark1(a,val,x+1,y+1);
    end
end
if x-1 >= 1 
    if a(y,x-1) < 220
        a = mark1(a,val,x-1,y);
    end
end
if x-1 >= 1 && y+1 <= height
    if a(y+1,x-1) < 220
        a = mark1(a,val,x-1,y+1);
    end
end
if x+1 <=width && y-1 >=1 
    if a(y-1,x+1) < 220
        a = mark1(a,val,x+1,y-1);
    end
end