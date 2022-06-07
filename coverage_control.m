clear;
clc;
world = [5 5];
world_density = @(x)  exp(-sum((x-[-1 -1]).^2));
% wd = {@(x) exp(-sum((x-[0 0]).^2)),@(x) exp(-sum((x-[5 5]).^2)), @(x) 1, @(x)exp(-x(1)^2), @(x)exp(-x(2)^2) };
% wd = {@(x) exp( -10*( (x(1)-2.5)^2 + (x(2)-2.5)^2 - 2)^2 ), @(x) exp(-(0.6 * x(1) + 0.8 * x(2) - 3))^2};

robot_num = 17;
grid_num = [5 5];

% rand_initial_pos = generate_initial_positions(world, robot_num, grid_num);
initial_pos = zeros(robot_num, 2);
for i = 1:robot_num
    initial_pos(i, :) = [5/robot_num*i 0];
end
rand_initial_pos = initial_pos;
robots = XIRHXQ_Robot_v1(robot_num, rand_initial_pos);
cvt = CVT(robot_num, world, world_density);

t_gap = 0.1;
t_total = 100;

filename = ['.\Images\' datestr(now,'mmddyy_HH-MM-SS_') num2str(robot_num) 'robots_cvt.gif'];

for iter_num = 1:(t_total / t_gap)
    
    pos = robots.posi;
    
    if iter_num <= 200
%         cvt.CVT_cal(pos, wd{floor((iter_num + 99) / 100)});
%         cvt.CVT_cal(pos, wd{1});
        cvt.CVT_cal(pos, @(x) exp(-10*( (x(1) - 2.5)^2 + (x(2) - 2.5)^2 - 2 )^2 ));
    elseif iter_num <= 500
        cvt.CVT_cal(pos, @(x) exp(-10*( (x(1) - 2.2 - 0.3*cos(iter_num / 100 * pi))^2 + (x(2) - 2.5 - 0.3*sin(iter_num / 100 * pi) )^2 - 2 )^2 ));
    else
        break;
    end
%     cvt.CVT_cal(pos);
    robots.velo = cvt.i_velo;
    
    res(iter_num, :) = sqrt(sum(cvt.i_velo.^2, 2));
    max_norm = max(sqrt(sum(cvt.i_velo.^2, 2)));
    
    robots.time_forward(t_gap);
    
    f = cvt.CVT_plot();
    
    save_gif(f, iter_num, t_gap, filename);
    
    if max_norm < 0.01
        break;
    end
    fprintf('Iteration #%d: Max Norm = %.4f\n', iter_num, max_norm);
end

clc;
% clear;
close all;
plot(res, 'LineWidth', 2);
% close all;