classdef XIRHXQ_Point < handle
    properties
        x(1, 1) {mustBeReal}
        y(1, 1) {mustBeReal}
    end
%{
    methods of XIRHXQ_Point:
    
    - XIRHXQ_Point(input_x, input_y)
        a point at (input_x, input_y)
    
    - XIRHXQ_Point([input_x input_y])
        a point at (input_x, input_y)
    
    - XIRHXQ_Point()
        a point at (0, 0) by default
    
    - plus(obj1, obj2) or 'obj1 + obj2'
    
    - minus(obj1, obj2) or 'obj1 - obj2'
    
    - uminus(obj1, obj2) or '-obj1'
    
    - mtimes(obj1, obj2) or 'obj1 * obj2'
        dot product of obj1 and obj2
    
    - mtimes(a, obj2) or 'a * obj2'
        scalar multiply of obj2
    
    - mtimes(obj1, a) or 'obj1 * a'
        scalar multiply of obj1
    
    - mrdivide(obj1, a) or 'obj1 / a'
        obj1 divide by a scalar
    
    - mpower(obj1, obj2) or 'obj1 ^ obj2'
        cross product of obj1 and obj2
    
    - lt(obj1, obj2) or 'obj1 < obj2'
        judging first by x and second by y
    
    - gt(obj1, obj2) or 'obj1 > obj2'
        same as lt
    
    - angle(obj) or obj.angle
        argument of obj based on cart2pol in (-pi, pi]
    
    - angle(obj1, obj2) or obj1.angle(obj2)
        argument of obj2-obj1 based on cart2pol in (-pi, pi]
    
    - len(obj) or obj.len
        2-norm of obj
    
    - len2(obj) or obj.len2
        square of 2-norm of obj
    
    - distance(obj1, obj2) or obj1.distance(obj2)
        Euclid distance between obj1 and obj2
    
    - normalize(obj) or obj.normalize
        scaling obj to unit vector
    
    - transform(obj, a) or obj.transform(a)
        scaling obj to a-length
    
    - saturation(obj, s) or obj.saturation(s)
        saturate obj to length s
    
    - rotate(obj, angle) or obj.rotate(angle) 
        rotate obj by angle around the origin
    
    - rotate_around(obj1, obj2, angle) or obj1.rotate(obj2, angle)
        rotate obj1 by angle around obj2
%}
    methods
        function obj = XIRHXQ_Point(varargin)
            if nargin > 1
                obj.x = varargin{1};
                obj.y = varargin{2};
            elseif nargin > 0
                if isa(varargin{1}, 'XIRHXQ_Point')
                    obj = varargin{1};
                else
                    obj.x = varargin{1}(1);
                    obj.y = varargin{1}(2);
                end
            else
                obj.x = 0;
                obj.y = 0;
            end
        end
        function res = eq(obj1, obj2)
           res = (obj1.x == obj2.x) && (obj1.y == obj2.y); 
        end
        function res = plus(obj1, obj2)
            res = XIRHXQ_Point(obj1.x + obj2.x, obj1.y + obj2.y);
        end
        function res = minus(obj1, obj2)
            res = XIRHXQ_Point(obj1.x - obj2.x, obj1.y - obj2.y);
        end
        function obj = uminus(obj)
            obj = XIRHXQ_Point(-obj.x, -obj.y);
        end
        function res = mtimes(obj1, obj2)
            if isnumeric(obj2)
                res = XIRHXQ_Point(obj1.x * obj2, obj1.y * obj2);
            elseif isnumeric(obj1)
                res = XIRHXQ_Point(obj1 * obj2.x, obj1 * obj2.y);
            else
                res = obj1.x * obj2.x + obj1.y * obj2.y;
            end
        end
        function res = mrdivide(obj, a)
            mustBeNonzero(a);
            res = XIRHXQ_Point(obj.x / a, obj.y / a);
        end
        function res = mpower(obj1, obj2)
            res = obj1.x * obj2.y - obj2.x * obj1.y;
        end
        function tf = lt(obj1, obj2)
            if obj1.x == obj2.x
                tf = obj1.y < obj2.y;
            else
                tf = obj1.x < obj2.x;
            end
        end
        function tf = gt(obj1, obj2)
            if obj1.x == obj2.x
                tf = obj1.y > obj2.y;
            else
                tf = obj1.x > obj2.x;
            end
        end
        function res = angle(varargin)
            if nargin == 1
                obj = varargin{1};
                [res, ~] = cart2pol(obj.x, obj.y);
            elseif nargin == 2
                obj1 = varargin{1};
                obj2 = varargin{2};
                [res, ~] = cart2pol(obj2.x - obj1.x, obj2.y - obj1.y);
            end
        end
        function res = len(obj)
            res = sqrt(obj.x^2 + obj.y^2);
        end
        function res = len2(obj)
            res = obj.x^2 + obj.y^2;
        end
        function res = distance(obj1, obj2)
            res = len(obj1 - obj2);
        end
        function obj = normalize(obj)
            obj = obj / len(obj);
        end
        function obj = transform(obj, a)
            obj = normalize(obj) * a;
        end
        function obj = saturation(obj, s)
            if obj.len > s
                obj = obj.normalize;
            end
        end
        function obj = rotate(obj, angle)
            c = cos(angle);
            s = sin(angle);
            obj = XIRHXQ_Point(obj.x * c - obj.y * s, obj.x * s + obj.y * c);
        end
        function obj = rotate_around(obj1, obj2, angle)
            vec = obj1 - obj2;
            c = cos(angle);
            s = sin(angle);
            obj = obj2 + XIRHXQ_Point(vec.x * c - vec.y * s, vec.x * s + vec.y * c);
        end
        function disp(obj)
            fprintf('A XIRHXQ_Point @ (%.2f, %.2f)\n', obj.x, obj.y);
        end
    end
end