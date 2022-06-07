function save_gif(frame, frame_number, tgap, file_name)
    [I, map] = rgb2ind(frame2im(getframe(frame)), 256);
    if frame_number == 1
        imwrite(I,map,file_name,'GIF', 'Loopcount',inf,'DelayTime', tgap);
    else
        imwrite(I,map,file_name,'GIF','WriteMode','append','DelayTime', tgap);
    end
end