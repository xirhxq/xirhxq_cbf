input_poly = polyshape([0 0;0 2; 2 2; 2 0]);
interior_point = [1 1];
density_f = @(x) exp(-sum((x-[0 0]).^2));
spacing = 0.2;
centroid_of_density(input_poly, interior_point, density_f, spacing);