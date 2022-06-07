classdef XIRHXQ_Line < handle
    properties
        s(1, 1) XIRHXQ_Point
        e(1, 1) XIRHXQ_Point
    end
%{
    methods of XIRHXQ_Line:
    
    - XIRHXQ_Line(start_point, end_point)
        !!! support XIRHXQ_Point type and vector type
        a line crossing start_point and end_point
    
    - XIRHXQ_Line(start_point, angle)
        a line crossing start_point with angle
    
    - XIRHXQ_Line(a, b, c)
        a line with equation ax + by + c = 0
    
    - adjust(obj)
        sort s and e such that s < e
    
    - length(obj)
        distance between start point and end point
    
    - angle(obj)
        angle of the line
    
    - relation(obj, p)
        the relation of p and the line
        -1: p is on the left/down
        1: p is on the right/up
        0: p is on the line
        
    - relation_to_seg(obj, p)
        the relation of p and the segment
        -2: p is not on the line
        -1: p is on the left/down
        1: p is on the right/up
        0: p is on the segment
    
    - is_on_line(obj, p)
        whether the point p is on the line
    
    - is_on_seg(obj, p)
        whether the point p is on the segment
    
    - parallel(obj1, obj2)
        whether obj1 is parallel to or same as obj2
    
    - is_the_same_line(obj1, obj2)
        whether obj1 is the same line as obj2
    
    - line_cross_line(obj1, obj2)
        whether line obj1 and line obj2 intersect
    
    - cross_point(obj1, obj2)
        !!! obj1 and obj2 must cross
        returns the cross_point
    
    - line_cross_seg(obj1, obj2)
        whether line obj1 and segment obj2 intersect
    
    - seg_cross_seg(obj1, obj2)
        whether segment obj1 and segment obj2 intersect
    
    - dis_point_to_line(obj, p)
        returns the distance from p to line obj
    
    - dis_point_to_seg(obj, p)
        returns the distance from p to segment obj
    
    - dis_seg_to_seg(obj, l)
        returns the distance from segment obj to segment l
    
    - project_point(obj, p)
        returns the project point of p on line obj
    
    - symmetry_point(obj, p)
        returns the symmetric point of p with respect to line obj
        
%}
    methods
        function obj = XIRHXQ_Line(varargin)
            if nargin == 2
                obj.s = XIRHXQ_Point(varargin{1});
                if isnumeric(varargin{2}) && isscalar(varargin{2})
                    angle = varargin{2};
                    obj.e = obj.s + XIRHXQ_Point(cos(angle), sin(angle));
                else
                    obj.e = XIRHXQ_Point(varargin{2});
                end
            elseif nargin == 3
                a = varargin{1};
                b = varargin{2};
                c = varargin{3};
                mustBeNumeric(a);mustBeNumeric(b);mustBeNumeric(c);
                if a == 0
                    obj.s = XIRHXQ_Point(0, -c/b);
                    obj.e = XIRHXQ_Point(1, -c/b);
                elseif b == 0
                    obj.s = XIRHXQ_Point(-c/a, 0);
                    obj.e = XIRHXQ_Point(-c/a, 1);
                else
                    obj.s = XIRHXQ_Point(0, -c/b);
                    obj.e = XIRHXQ_Point(1, -(c+a)/b);
                end
            end
            if obj.s > obj.e
                tmp = obj.s;
                obj.s = obj.e;
                obj.e = tmp;
            end
        end
        function obj = adjust(obj)
            if obj.s > obj.e
                tmp = obj.s;
                obj.s = obj.e;
                obj.e = tmp;
            end
        end
        function res = length(obj)
            res = distance(obj.s, obj.e);
        end
        function res = angle(obj)
            res = obj.s.angle(obj.e);
        end
        function res = relation(obj, p)
            p = XIRHXQ_Point(p);
            c = (p - obj.s) ^ (p - obj.e);
            if c > 0
                res = 1;
            elseif c < 0
                res = -1;
            else
                res = 0;
            end
        end
        function res = relation_to_seg(obj, p)
            p = XIRHXQ_Point(p);
            if obj.relation(p) ~= 0
                res = -2;
            elseif p > obj.e
                res = 1;
            elseif p < obj.s
                res = -1;
            else
                res = 0;
            end
         end
        function res = is_on_line(obj, p)
            p = XIRHXQ_Point(p);
            res = (obj.relation(p) == 0);
        end
        function res = is_on_seg(obj, p)
            p = XIRHXQ_Point(p);
            res = (obj.relation(p) == 0) && ((p - obj.s) * (p - obj.e) <= 0);
        end
        function res = parallel(obj1, obj2)
            mustBeA(obj1, 'XIRHXQ_Line');
            mustBeA(obj2, 'XIRHXQ_Line');
            res = ((obj1.e - obj1.s) ^ (obj2.e - obj2.s) == 0);
        end
        function res = is_the_same_line(obj1, obj2)
            mustBeA(obj1, 'XIRHXQ_Line');
            mustBeA(obj2, 'XIRHXQ_Line');
            res = (is_on_line(obj1, obj2.s) && is_on_line(obj1, obj2.e));
        end
        function res = line_cross_line(obj1, obj2)
            mustBeA(obj1, 'XIRHXQ_Line');
            mustBeA(obj2, 'XIRHXQ_Line');
            res = ~parallel(obj1, obj2);
        end
        function res = cross_point(obj1, obj2)
            mustBeA(obj1, 'XIRHXQ_Line');
            mustBeA(obj2, 'XIRHXQ_Line');
            a1 = (obj2.e - obj2.s) ^ (obj1.s - obj2.s);
            a2 = (obj2.e - obj2.s) ^ (obj1.e - obj2.s);
            if parallel(obj1, obj2)
                error('Not Crossing');
            end
            res = XIRHXQ_Point((obj1.s.x * a2 - obj1.e.x * a1) / (a2 - a1), (obj1.s.y * a2 - obj1.e.y * a1) / (a2 - a1));
        end
        function res = line_cross_seg(obj1, obj2)
            mustBeA(obj1, 'XIRHXQ_Line');
            mustBeA(obj2, 'XIRHXQ_Line');
            if is_the_same_line(obj1, obj2)
                error('Same Line');
            else
                res = (obj1.relation(obj2.s) * obj1.relation(obj2.e) < 0);
            end
        end
        function res = seg_cross_seg(obj1, obj2)
            mustBeA(obj1, 'XIRHXQ_Line');
            mustBeA(obj2, 'XIRHXQ_Line');
            if is_the_same_line(obj1, obj2)
                res = (obj1.relation_to_seg(obj2.s) * obj1.relation_to_seg(obj2.e) <= 0);
            elseif parallel(obj1, obj2)
                res = false;
            else
                cp = cross_point(obj1, obj2);
                res = obj1.is_on_seg(cp) && obj2.is_on_seg(cp);
            end
        end
        function res = dis_point_to_line(obj, p)
            p = XIRHXQ_Point(p);
            res = abs((p - obj.s) ^ (p - obj.e)) / obj.length;
        end
        function res = dis_point_to_seg(obj, p)
            p = XIRHXQ_Point(p);
            if (p - obj.s) * (obj.e - obj.s) < 0 || (p - obj.e) * (obj.s - obj.e) < 0
                res = min(p.distance(obj.s), p.distance(obj.e));
            else
                res = obj.dis_point_to_line(p);
            end
        end
        function res = dis_seg_to_seg(obj1, obj2)
            mustBeA(obj1, 'XIRHXQ_Line');
            mustBeA(obj2, 'XIRHXQ_Line');
            res = min(min(obj1.dis_point_to_seg(obj2.s), obj1.dis_point_to_seg(obj2.e)),...
                      min(obj2.dis_point_to_seg(obj1.s), obj2.dis_point_to_seg(obj1.e)));
        end
        function res = project_point(obj, p)
            p = XIRHXQ_Point(p);
            res = obj.s + (obj.e - obj.s) * ((obj.e - obj.s) * (p - obj.s)) / len2(obj.e - obj.s);
        end
        function res = symmetry_point(obj, p)
            mid = project_point(obj, p);
            res = mid * 2 - p;
        end
        function disp(obj)
            fprintf('A XIRHXQ_Line from (%.2f, %.2f) to (%.2f, %.2f)\n', obj.s.x, obj.s.y, obj.e.x, obj.e.y);
        end
    end
    methods(Static)
        function res = midean_line(p1, p2)
            p1 = XIRHXQ_Point(p1);
            p2 = XIRHXQ_Point(p2);
            res = XIRHXQ_Line((p1+p2)/2, angle(p2-p1) + pi/2);
        end
    end
end