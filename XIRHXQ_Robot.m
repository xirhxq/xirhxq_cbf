classdef XIRHXQ_Robot < handle
    properties
        n(1, 1) {mustBeInteger}
        v XIRHXQ_Point
        p XIRHXQ_Point
        s(1, 1) {mustBePositive} = 1
    end
    methods
        function obj = XIRHXQ_Robot(varargin)
            if nargin > 3 || nargin < 2
                error('Initialize Error: Invalid Input');
            else
                obj.n = varargin{1};
                if isnumeric(varargin{2})
                    for i = obj.n : -1 : 1
                        obj.p(i) = XIRHXQ_Point(varargin{2}(i, :));
                    end
                else
                    obj.p = varargin{2};
                end
                if nargin == 3
                    if isnumeric(varargin{3})
                        for i = obj.n : -1 : 1
                            obj.v(i) = XIRHXQ_Point(varargin{3}(i, :));
                        end
                    else
                        obj.v = varargin{3};
                    end
                end
            end
        end
        function obj = set_saturation(obj, saturation)
            obj.s = saturation;
        end
        function obj = set_velocity(obj, velo)
            if isnumeric(velo)
                if size(velo, 1) ~= obj.n || size(velo, 2) ~= 2
                    error('Wrong size of velocity input');
                end
                for i = 1:obj.n
                    obj.v(i) = XIRHXQ_Point(velo(i, :));
                end
            else
                obj.v = velo;
            end
        end
        function obj = time_forward(obj, time)
            for i = 1:obj.n
                obj.p(i) = obj.p(i) + time * obj.v(i).saturation(obj.s);
            end
        end
    end
end