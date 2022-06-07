classdef XIRHXQ_Polygon < handle
    properties
        n(1, 1) {mustBeInteger}
        v XIRHXQ_Point
        inner_point XIRHXQ_Point
    end
%{
    methods of XIRHXQ_Polygon:
    
    - index_after(obj, n, d)
        the index of (n+d) in {1, 2, ..., obj.n}
    
    - copy(obj)
        returns a copy of obj
    
    - XIRHXQ_Polygon(points)
        initialize XIRHXQ_Polygon by XIRHXQ_Point
    
    - XIRHXQ_Polygon(vectors)
        initialize XIRHXQ_Polygon by position vectors
    
    - get_screen(obj)
        get plot screen limit range
        returns x_range and y_range
    
    - get_inner_point(obj)
        get a point inside the polygon
    
    - get_random_point(obj)
        get a random point inside
    
    - polar_sorting(obj)
        sort the vertices by polar angle
    
    - simplify(obj)
        deleting the identical points
    
    - checking_convex(obj)
        checking the convexity of the polygon
    
    - rearrange(obj)
        packing get_inner_point/polar_sorting/simplify/checking_convex together
 
    - plot(obj)
        ploting the polygon
    
    - disp(obj)
        overload the disp method for XIRHXQ_Polygon
    
    - direct_add(obj, p)
        adding a point directly
    
    - direct_delete_at_position(obj, p)
        deleting a point at p directly
    
    - direct_delete_at_index(obj, index)
        deleting index th point directly
    
    - add_one_point(obj, p)
        add a point and rearrange the polygon
    
    - delete_one_point_at_index(obj, p)
        deleting index th point and rearrange the polygon
    
    - delete_one_point_at_position(obj, p)
        deleting a point at p and rearrange the polygon
    
    - intersect_with_halfplane(obj, line, dir)
        updates obj as the intersection with line and direction
 
    - intersect_with_polygon(obj1, obj2)
        updates obj1 as the intersection of obj1 and obj2
    
    - circumference(obj)
        returns the circumference of obj
    
    - area(obj)
        returns the area of obj
    
    - area_with_function(obj, f)
        2-D integral of function f within obj 
%}
    methods
        function nxt = index_after(obj, n, d)
            nxt = n + mod(d, obj.n);
            if nxt > obj.n
                nxt = nxt - obj.n;
            end
        end
        function res = copy(obj)
            res = XIRHXQ_Polygon(obj.v);
        end
        function obj = XIRHXQ_Polygon(varargin)
            if nargin == 1
                if isnumeric(varargin{1})
                    if size(varargin{1}, 2) ~= 2
                        error('Initialize Error: Wrong Size of Input');
                    elseif size(varargin{1}, 1) < 3
                        error('Initialize Error: Not Enough Points');
                    end
                    obj.n = size(varargin{1}, 1);
                    for i = obj.n:-1:1
                        obj.v(i) = varargin{1}(i, :);
                    end
                else
                    if size(varargin{1}, 2) < 3
                        error('Initialize Error: Not Enough Points');
                    end
                    obj.n = numel(varargin{1});
                    for i = obj.n:-1:1
                        obj.v(i) = XIRHXQ_Point(varargin{1}(i));
                    end
                end
                obj.get_inner_point;
                obj.polar_sorting;
                obj.simplify;
                obj.checking_convex;
                if obj.n < 3
                    error('Initialize Error: Not enough points');
                end
            elseif nargin > 2
                error('Initialize Error: Inputs more than enough');
            end
        end
        function [xlimit, ylimit] = get_screen(obj)
            xlimit = [obj.v(1).x obj.v(1).x];
            ylimit = [obj.v(1).y obj.v(1).y];
            for i = 2:obj.n
                xlimit(1) = min(xlimit(1), obj.v(i).x);
                xlimit(2) = max(xlimit(2), obj.v(i).x);
                ylimit(1) = min(ylimit(1), obj.v(i).y);
                ylimit(2) = max(ylimit(2), obj.v(i).y);
            end
            xlimit = mean(xlimit) + (xlimit - mean(xlimit)) * 1.2;
            ylimit = mean(ylimit) + (ylimit - mean(ylimit)) * 1.2;
        end
        function get_inner_point(obj)
            obj.inner_point = XIRHXQ_Point(0, 0);
            for i = 1:obj.n
                obj.inner_point = obj.inner_point + obj.v(i);
            end
            obj.inner_point = obj.inner_point / obj.n;
            for i = 1:obj.n
                if obj.v(i) == obj.inner_point
                    error('A point is at the center, not convex.');
                end
            end
        end
        function rp = get_random_point(obj)
            id = randi(obj.n);
            rd = [rand, rand, rand];
            rd = rd / sum(rd);
            rp = obj.inner_point * rd(1) + obj.v(id) * rd(2) + obj.v(obj.index_after(id, 1)) * rd(3);
        end
        function polar_sorting(obj)
            for i = 1:obj.n - 1
                for j = 1:obj.n - i
                    if angle(obj.v(j) - obj.inner_point) > angle(obj.v(j + 1) - obj.inner_point)
                        tmp_point = obj.v(j);
                        obj.v(j) = obj.v(j + 1);
                        obj.v(j + 1) = tmp_point;
                    end
                end
            end
        end
        function simplify(obj)
            for i = 2:obj.n
                if i > obj.n
                    break;
                end
                if obj.v(i) == obj.v(i - 1)
                    obj.v(i) = [];
                    obj.n = obj.n - 1;
                    warning('Deleting identical points');
                end
            end
            for i = 1:obj.n
                if i > obj.n
                    break;
                end
                l_pre = XIRHXQ_Line(obj.v(obj.index_after(i, -1)), obj.v(i));
                l_nxt = XIRHXQ_Line(obj.v(obj.index_after(i, 1)), obj.v(i));
                if obj.n > 2 && is_the_same_line(l_pre, l_nxt)
                    obj.v(i) = [];
                    obj.n = obj.n - 1;
                    warning('Deleting colinear points');
                end
            end
        end
        function checking_convex(obj)
            for i = 1:obj.n
                if i > obj.n
                    break;
                end
                vec_pre = obj.v(i) - obj.v(obj.index_after(i, 1));
                vec_nxt = obj.v(obj.index_after(i, 2)) - obj.v(obj.index_after(i, 1));
                if vec_pre ^ vec_nxt > 1e-6
                    error('Polygon not convex');
                end
            end
        end
        function rearrange(obj)
            if obj.n < 3
                error('Not enough points.');
            end
            obj.get_inner_point;
            obj.polar_sorting;
            obj.simplify;
            obj.checking_convex;
        end
        function plot(obj)
            for i = 1:obj.n
                plot([obj.v(i).x obj.v(mod(i,obj.n)+1).x], [obj.v(i).y obj.v(mod(i, obj.n)+1).y], 'k', 'LineWidth', 2);
                hold on;
            end
            [xlimit, ylimit] = obj.get_screen;
            xlim(xlimit);
            ylim(ylimit);
        end
        function disp(obj)
            fprintf('A XIRHXQ_Polygon with %d points:\n', obj.n);
            for i = 1:obj.n
                if i > 1
                    fprintf('--');
                end
                if mod(i,5) == 0
                    fprintf('\n');
                end
                fprintf('(%.2f,%.2f)', obj.v(i).x, obj.v(i).y);
            end
            fprintf('\n');
        end
        function obj = direct_add(obj, p)
            p = XIRHXQ_Point(p);
            obj.n = obj.n + 1;
            obj.v(obj.n) = p;
        end
        function obj = direct_delete_at_position(obj, p)
            p = XIRHXQ_Point(p);
            for i = 1:obj.n
               if i > obj.n
                   break
               end
               if obj.v(i) == p
                   obj.v(i) = [];
                   obj.n = obj.n - 1;
               end
            end
        end
        function obj = direct_delete_at_index(obj, index)
            obj.v(index) = [];
            obj.n = obj.n - 1;
        end
        function obj = add_one_point(obj, p)
            obj.direct_add(p);
            obj.rearrange;
        end
        function obj = delete_one_point_at_index(obj, index)
            obj.direct_delete_at_index(index);
            obj.rearrange;
        end
        function obj = delete_one_point_at_position(obj, p)
            obj.direct_delete_at_poisition(p);
            obj.rearrange;
        end
        function obj = intersect_with_halfplane(obj, line, dir)
            if isa(dir, 'XIRHXQ_Point')
                dir = line.relation(dir);
            end
            cp_cnt = 0;
            for i = 1:obj.n
                l = XIRHXQ_Line(obj.v(i), obj.v(obj.index_after(i, 1)));
                if ~line.is_the_same_line(l) && line.line_cross_seg(l)
                   cp_cnt = cp_cnt + 1;
                   cp(cp_cnt) = line.cross_point(l);
                end
            end
            dl_cnt = 0;
            for i = 1:obj.n
                if line.relation(obj.v(i)) == -dir
                    dl_cnt = dl_cnt + 1;
                    dl(dl_cnt) = obj.v(i);
                end
            end
            for i = 1:cp_cnt
                obj.direct_add(cp(i));
            end
            for i = 1:dl_cnt
                obj.direct_delete_at_position(dl(i));
            end
            obj.rearrange;
        end
        function obj1 = intersect_with_polygon(obj1, obj2)
            for i = 1:obj2.n
                l = XIRHXQ_Line(obj2.v(i), obj2.v(obj2.index_after(i, 1)));
                obj1.intersect_with_halfplane(l, obj2.inner_point);
            end
        end
        function res = circumference(obj)
            res = 0;
            for i = 1:obj.n
                l = XIRHXQ_Line(obj2.v(i), obj2.v(obj2.index_after(i, 1)));
                res = res + l.length;
            end
        end
        function res = area(obj)
            res = 0;
            for p = 1:obj.n
                vec_now = obj.v(p) - obj.inner_point;
                vec_nxt = obj.v(obj.index_after(p, 1)) - obj.inner_point;
                res = res + abs(vec_now ^ vec_nxt) / 2;
            end
        end
        function res = area_with_function(obj, f)
            obj.rearrange;
            spacing = 0.1;
            res = 0;
            for p = 1:obj.n
                vec_now = obj.v(p) - obj.inner_point;
                vec_nxt = obj.v(obj.index_after(p, 1)) - obj.inner_point;
                k = floor(max(vec_now.len, vec_nxt.len) / spacing) + 1;
                for i = 0:k-1
                    for j = 0:k-i-1
                        tmp_point(1) = obj.inner_point + i / k * vec_now + j / k * vec_nxt;
                        tmp_point(2) = obj.inner_point + (i + 1) / k * vec_now + j / k * vec_nxt;
                        tmp_point(3) = obj.inner_point + i / k * vec_now + (j + 1) / k * vec_nxt;
                        center = (tmp_point(1) + tmp_point(2) + tmp_point(3)) / 3;
                        res = res + abs((tmp_point(1) - tmp_point(2)) ^ (tmp_point(2) - tmp_point(3))) / 2 * f(center);
                    end
                end
                for i = 0:k-2
                    for j = 0:k-i-2
                        tmp_point(1) = obj.inner_point + i / k * vec_now + (j + 1) / k * vec_nxt;
                        tmp_point(2) = obj.inner_point + (i + 1) / k * vec_now + j / k * vec_nxt;
                        tmp_point(3) = obj.inner_point + (i + 1) / k * vec_now + (j + 1) / k * vec_nxt;
                        center = (tmp_point(1) + tmp_point(2) + tmp_point(3)) / 3;
                        res = res + abs((tmp_point(1) - tmp_point(2)) ^ (tmp_point(2) - tmp_point(3))) / 2 * f(center);
                    end
                end
            end
        end
    end
end