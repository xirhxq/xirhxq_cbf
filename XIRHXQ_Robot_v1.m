classdef XIRHXQ_Robot_v1 < handle
    properties
        velo
        posi
        robot_number
    end
    methods
        function obj = XIRHXQ_Robot_v1(rn, pos, vel)
            if nargin > 1
                obj.robot_number = rn;
                if size(pos, 1) ~= rn || size(pos, 2) ~= 2
                    error('Initialize Error: Wrong Size of Position Matrix');
                end
                obj.posi = pos;
                if nargin > 2
                    if size(vel, 1) ~= rn || size(vel, 2) ~= 2
                        error('Initialize Error: Wrong Size of Velocity Matrix');
                    end
                    obj.velo = vel;
                else
                    obj.velo = zeros(rn, 2);
                end
            else
                obj.robot_number = 1;
                obj.posi = [0 0];
                obj.velo = [0 0];
            end
        end
        function obj = time_forward(obj, time_step)
            obj.posi = obj.posi + time_step .* obj.velo;
        end
    end
end