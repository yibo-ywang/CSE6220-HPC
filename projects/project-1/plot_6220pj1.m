x = [1, 2, 4, 8, 16]
y = [0.037005, 0.019703, 0.010148, 0.005282, 0.002683]
plot(x, y, 'LineWidth',2)
ylabel('Runtime [s]')
ylabel('Number of Processors')
title('Runtime vs Number of Processors')

x = [5000000,2500001,1250002,625003,312504]
y = [0.037005, 0.019703, 0.010148, 0.005282, 0.002683]
plot(x, y, 'LineWidth',2)
ylabel('Runtime [s]')
xlabel('n/p+log(p)')
title('Runtime vs n/p+log(p) (n = 5000000)')

x = [5000000,10000000,20000000,40000000,80000000,160000000]
y=[0.010138, 0.020239, 0.041361, 0.080369, 0.161331, 0.323059]
plot(x, y, 'LineWidth',2)
ylabel('Runtime [s]')
xlabel('Value of N')
title('Runtime vs N (Running on 4 processors)')

