function [centroid_x, centroid_y, moment, mass, area] = centroid_of_density(input_poly, interior_point, density_function, spacing)
    input_poly.Vertices;
    point_number = size(input_poly.Vertices, 1);
    area = polyarea(input_poly.Vertices(:, 1), input_poly.Vertices(:, 2));
    moment = [0 0];
    mass = 0;
    for k = 1:point_number
        previous_point = input_poly.Vertices(k, :);
        previous_vector = previous_point - interior_point;
        next_point = input_poly.Vertices(mod(k, point_number) + 1, :);
        next_vector = next_point - interior_point;
        part_poly = [previous_point; next_point; interior_point];
        part_area = polyarea(part_poly(:, 1), part_poly(:, 2));
        if part_area == 0
            continue;
        end
        n = floor(max(norm(previous_point - interior_point), norm(next_point - interior_point)) / spacing) + 1;
        for i = 0:n-1
            for j = 0:n-1-i
                tmp_point_1 = (i) / n * previous_vector + (j) / n * next_vector + interior_point;
                tmp_point_2 = (i + 1) / n * previous_vector + (j) / n * next_vector + interior_point;
                tmp_point_3 = (i) / n * previous_vector + (j + 1) / n * next_vector + interior_point;
                [tmp_point_1; tmp_point_2; tmp_point_3];
                tmp_point = (i + 1/3) / n * previous_vector + (j + 1/3) / n * next_vector + interior_point;
                moment = moment + part_area / n^2 .* density_function(tmp_point) .* tmp_point;
                mass = mass + part_area / n^2 * density_function(tmp_point);
            end
        end
        for i = 1:n-1
            for j = 1:n-i
                tmp_point_1 = (i) / n * previous_vector + (j) / n * next_vector + interior_point;
                tmp_point_2 = (i - 1) / n * previous_vector + (j) / n * next_vector + interior_point;
                tmp_point_3 = (i) / n * previous_vector + (j - 1) / n * next_vector + interior_point;
                [tmp_point_1; tmp_point_2; tmp_point_3];
                tmp_point = (i - 1/3) / n * previous_vector + (j - 1/3) / n * next_vector + interior_point;
                moment = moment + part_area / n^2 .* density_function(tmp_point) .* tmp_point;
                mass = mass + part_area / n^2 * density_function(tmp_point);
            end
        end
    end
    centroid = moment ./ mass;
    centroid_x = centroid(1, 1);
    centroid_y = centroid(1, 2);
end