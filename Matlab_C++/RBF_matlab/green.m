function greenValue = green(x, c, delta)
    greenValue = exp(-1.0 * sum((x - c).^2) / (2 * delta^2));
end