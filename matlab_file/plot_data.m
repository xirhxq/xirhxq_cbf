pos = readmatrix('.\data\12-30_19-42_pos.txt');
poly = readmatrix('.\data\12-30_19-42_poly.txt', 'Range',[1 1 5000 15]);

n = 5;

file_name = ['.\data\' datestr(now,'mmddyy_HH-MM-SS_') num2str(n) 'robots_cvt.gif'];
for iter = 1:size(pos, 1)
    iter
    f = figure('Visible', 'off',  'position', [50 50 1000 500]);
    xlim([-6 6]);
    ylim([-1 6]);
    axis equal;
    for i = 1:n
        plot(pos(iter, i*2 - 1), pos(iter, i * 2), 'bo');
        hold on;
    end
    for i = 1:n
        r = iter * 5 - 5 + i;
        num = poly(r, 1);
        for j = 1:num-1
            plot([poly(r, j * 2) poly(r, j * 2 + 2)], [poly(r, j * 2 + 1) poly(r, j * 2 + 3)], 'k');
        end
        plot([poly(r, 2) poly(r, num * 2)], [poly(r, 3) poly(r, num * 2 + 1)], 'k');
    end
    [I, map] = rgb2ind(frame2im(getframe(f)), 256);
    if iter == 1
        imwrite(I,map,file_name,'GIF', 'Loopcount',inf,'DelayTime', 0.1);
    else
        imwrite(I,map,file_name,'GIF','WriteMode','append','DelayTime', 0.1);
    end
    hold off;
    close all;
end