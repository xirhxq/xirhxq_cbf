function positions = generate_initial_positions(wd, rn, gn)
    rand_grid_index = randperm(prod(gn), rn);
    [rand_row, rand_col] = ind2sub(gn, rand_grid_index);
    rand_grid_index = [rand_row' rand_col'];

    grid_size = wd ./ gn;

    positions = (rand_grid_index - rand(size(rand_grid_index))) .* grid_size;
end