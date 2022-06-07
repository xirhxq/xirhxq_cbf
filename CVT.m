classdef CVT < handle
    properties (SetAccess = protected)
        world
        world_poly
        world_density
        i_poly
        i_area
        i_mass
        i_moment
        i_centroid
        i_velo
        robot_number = -1
        points
        outside_points
        spacing = 0.1
    end
    methods
        function obj = CVT(rn, wd, dst)
            obj.robot_number = rn;
            obj.world = wd;
            obj.world_poly = polyshape([0 0 wd(1) wd(1)], [0 wd(2) wd(2) 0]);
            center = wd ./ 2;
            obj.world_density = dst;
            obj.outside_points = [center(1)-3*wd(1) center(2)-3*wd(2);...
                                  center(1)-3*wd(1) center(2)+3*wd(2);...
                                  center(1)+3*wd(1) center(2)-3*wd(2);...
                                  center(1)+3*wd(1) center(2)+3*wd(2);...
                                  -4*wd(1) 5*wd(2);...
                                  5*wd(1) 5*wd(2);...
                                  -4*wd(1) -4*wd(2);...
                                  5*wd(1) -4*wd(2);...
                                  ];
            obj.points = zeros(rn, 2);
            obj.i_poly = obj.world_poly;
        end
        function CVT_cal(obj, pts, dst)
            obj.world_density = dst;
            obj.points = pts;
            DT = delaunayTriangulation([pts; obj.outside_points]);
            [V_vertices, V_regions] = voronoiDiagram(DT);
            obj.i_poly(obj.robot_number) = polyshape;
            for i = 1:obj.robot_number
                i_vertices = V_vertices(V_regions{i}, :);
                if i_vertices(1, 1) == inf
                    i_vertices(1, :) = [];
                end
                obj.i_poly(i) = intersect(obj.world_poly, polyshape(i_vertices));
                [obj.i_centroid(i, 1), obj.i_centroid(i,2), obj.i_moment(i, :), obj.i_mass(i, :), obj.i_area(i, :)] = ...
                    centroid_of_density(obj.i_poly(i), obj.points(i, :), obj.world_density, obj.spacing);
%                 [obj.i_centroid(i, 1), obj.i_centroid(i,2)] = centroid(obj.i_poly(i));
                obj.i_velo(i, :) = obj.i_centroid(i, :) - pts(i, :);
            end
        end
        function fig = CVT_plot(obj)
            f = figure('Visible', 'off', 'position', [50 50 1000 1000]);
            axis equal;
            plot(obj.points(:, 1), obj.points(:, 2), '.b');
            hold on;
            x = linspace(0, obj.world(1));
            y = linspace(0, obj.world(2));
            [X, Y] = meshgrid(x, y);
            for i = size(X, 1): -1 : 1
                for j = size(X, 2): -1: 1
                    Z(i, j) = obj.world_density([X(i, j), Y(i, j)]);
                end
            end
            tf = obj.world_density;
%             contour(X, Y, Z, [tf([5 0]) tf([10 0]) tf([15 0]) tf([20 0]) tf([25 0])], 'ShowText', 'on');
            contour(X, Y, Z, 10);
            for i = 1:obj.robot_number
                plot(obj.i_poly(i));
                hold on;
%                 text(obj.i_centroid(i, 1), obj.i_centroid(i, 2), ...
%                     {num2str(obj.i_moment(i, :)), num2str(obj.i_mass(i, :)), num2str(obj.i_area(i, :))});
                hold on;
                plot(obj.i_centroid(i, 1), obj.i_centroid(i, 2), 'r*');
                hold on;
                plot([obj.points(i, 1) obj.i_centroid(i, 1)], [obj.points(i, 2) obj.i_centroid(i, 2)], 'g');
                hold on;
            end
            xlim([0, obj.world(1)]);
            ylim([0, obj.world(2)]);
            fig = f;
            hold off;
        end
    end
end