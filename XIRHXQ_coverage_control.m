clear
clc
world = XIRHXQ_Polygon([0 0; 5 0; 0 5; 5 5]);
world_density = @(p) exp(-(p.x ^ 2 + p.y ^ 2));

robot_num = 17;
grid_num = floor(sqrt(robot_num)) + 1;

for i = robot_num : -1 : 1
%     position(i) = world.get_random_point
    position(i) = XIRHXQ_Point(rand*5, rand*5);
end

cvt = XIRHXQ_CVT(position, world);
r = XIRHXQ_Robot(robot_num, position);

filename = ['.\Images\' datestr(now,'mmddyy_HH-MM-SS_') num2str(robot_num) 'robots_cvt.gif'];

for t = 1:100
    cvt.cal_poly;
    centroid = cvt.get_centroid(world_density);
    
    f = figure('Visible', 'off', 'position', [50 50 1000 1000]);
    axis equal;
    for i = 1:robot_num
        plot(cvt.poly(i));
        plot(position(i).x, position(i).y, 'bo');
        plot(centroid(i).x, centroid(i).y, 'r*');
        plot([position(i).x centroid(i).x], [position(i).y centroid(i).y], 'g');
        hold on;
    end
    [xlimit, ylimit] = world.get_screen;
    xlim(xlimit);ylim(ylimit);
    hold off;
    
    save_to_gif(f, t, 0.1, filename);
    
    for i = robot_num:-1:1
        velocity(i) = centroid(i) - position(i);
    end
    r.set_velocity(velocity);
    r.time_forward(0.1);
    position = r.p;
    cvt.reset_point(position);
    fprintf('Iteration #%03d\n', t);
end
close all;