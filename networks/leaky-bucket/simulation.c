#include <stdio.h>

int main()
{
    int max_steps, bucket_size = 0, max_capacity, leak_rate;
    printf("Enter the number of time steps (iterations): ");
    scanf("%d", &max_steps);
    int incoming_pkts[max_steps];
    for (int i = 0; i < max_steps; i++)
    {
        printf("Enter the number of incoming packets during %dth time step: ", i);
        scanf("%d", &incoming_pkts[i]);
    }
    printf("Enter the max bucket capacity: ");
    scanf("%d", &max_capacity);
    printf("Enter the bucket's leak rate: ");
    scanf("%d", &leak_rate);
    for (int i = 0; i < max_steps; i++)
    {
        printf("Step %d: %d packets flowing in...\n", i, incoming_pkts[i]);
        int dropped = bucket_size + incoming_pkts[i] - max_capacity;
        if (dropped > 0)
        {
            printf("Overflow. dropped %d packets!\n", dropped);
            bucket_size += incoming_pkts[i] - dropped;
        }
        else
        {
            bucket_size += incoming_pkts[i];
        }
        printf("Current bucket size: %d\n", bucket_size);
        int packets_remaining = bucket_size - leak_rate;
        if (packets_remaining > 0)
        {
            printf("Leaking out %d packets\n", leak_rate);
            bucket_size = packets_remaining;
        }
        else
        {
            printf("Leaking out %d packets\n", bucket_size);
            bucket_size = 0;
        }
        printf("Bucket size after leak: %d\n", bucket_size);
    }
    printf("Emptying the bucket...\n");
    while (bucket_size > 0)
    {
        printf("Current bucket size: %d\n", bucket_size);
        int packets_remaining = bucket_size - leak_rate;
        if (packets_remaining > 0)
        {
            printf("Leaking out %d packets\n", leak_rate);
            bucket_size = packets_remaining;
        }
        else
        {
            printf("Leaking out %d packets\n", bucket_size);
            bucket_size = 0;
        }
        printf("Bucket size after leak: %d\n", bucket_size);
    }
    printf("Bucket empty!\n");
    return 0;
}