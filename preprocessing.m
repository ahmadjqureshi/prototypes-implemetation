function a=preprocessing(img,imgwrite)
a = imread(img);

a = rgb2gray(a);

hw = size(a);

height = hw(1);
width = hw(2); 

for y=1:height
    for x=1:width
        if a(y,x) < 230
            a(y,x)=0;
        else
            a(y,x)=255;
        end
    end
end

imwrite(a,imgwrite,'JPEG');