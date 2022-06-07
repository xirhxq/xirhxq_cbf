classdef XIRHXQ_CVT < handle
    properties
        n(1, 1) {mustBeInteger}
        point XIRHXQ_Point
        poly XIRHXQ_Polygon
        world XIRHXQ_Polygon
    end
    methods
        function obj = XIRHXQ_CVT(varargin)
            if nargin == 2
                if isnumeric(varargin{1})
                    if size(varargin{1}, 2) ~= 2
                        error('Wrong Size of Input');
                    end
                    obj.n = size(varargin{1}, 1);
                    for i = obj.n:-1:1
                        obj.point(i) = XIRHXQ_Point(varargin{1}(i, :));
                    end
                else
                    obj.n = numel(varargin{1});
                    for i = obj.n:-1:1
                        obj.point(i) = varargin{1}(i);
                    end
                end
                obj.world = varargin{2}.copy;
                for i = obj.n:-1:1
                    obj.poly(i) = varargin{2}.copy;
                end
            else
                error('Invalid input');
            end
        end
        function obj = reset_point(obj, pts)
            if isnumeric(pts)
                for i = 1:obj.n
                    obj.point(i) = XIRHXQ_Point(pts(i, :));
                end
            else
                obj.point = pts;
            end
            for i = 1:obj.n
                obj.poly(i) = obj.world.copy;
            end
        end
        function obj = cal_poly(obj)
            for i = 1:obj.n
                for j = 1:obj.n
%                     fprintf('i = %d, j = %d\n', i, j);
                    if i == j
                        continue;
                    end
%                     obj.point(i)
%                     obj.point(j)
%                     XIRHXQ_Line.midean_line(obj.point(i), obj.point(j))
                    obj.poly(i).intersect_with_halfplane(XIRHXQ_Line.midean_line(obj.point(i), obj.point(j)), obj.point(i));
%                     obj.poly(i)
                end
            end
        end
        function disp(obj)
            fprintf('A XIRHXQ_CVT with %d points\n', obj.n);
            for i = 1:obj.n
                fprintf('Point #%d @ (%.2f, %.2f):\n', i, obj.point(i).x, obj.point(i).y);
                disp(obj.poly(i));
            end
        end
        function plot(obj)
%             figure('Visible', 'off');
            figure;
            for i = 1:obj.n
                plot(obj.poly(i));
                hold on;
            end
            [xlimit, ylimit] = obj.world.get_screen;
            xlim(xlimit);ylim(ylimit);
        end
        function c = get_centroid(obj, f)
            for i = obj.n:-1:1
                c(i,:) = XIRHXQ_Point([obj.poly(i).area_with_function(@(x)f(x)*x.x) obj.poly(i).area_with_function(@(x)f(x)*x.y)])...
                         / obj.poly(i).area_with_function(f);
            end
        end
    end
end