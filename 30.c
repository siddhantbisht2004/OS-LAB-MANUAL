#include <stdio.h>
#include <stdlib.h>

#define LOW 0
#define HIGH 199

int main()
{
    int queue[20], q_size, temp, head, sum = 0, dloc;

    printf("Input number of disk locations: ");
    scanf("%d", &q_size);

    printf("Enter head position: ");
    scanf("%d", &head);

    printf("Input elements into disk queue:\n");
    for (int i = 0; i < q_size; i++)
        scanf("%d", &queue[i]);

    // Add head to queue
    queue[q_size] = head;
    q_size++;

    // Sort queue
    for (int i = 0; i < q_size - 1; i++)
    {
        for (int j = i + 1; j < q_size; j++)
        {
            if (queue[i] > queue[j])
            {
                temp = queue[i];
                queue[i] = queue[j];
                queue[j] = temp;
            }
        }
    }

    // Find head location after sorting
    for (int i = 0; i < q_size; i++)
    {
        if (queue[i] == head)
        {
            dloc = i;
            break;
        }
    }

    printf("\nDisk movement order:\n");

    // Move towards lower end first if closer, else towards higher end
    if (abs(head - LOW) <= abs(head - HIGH))
    {
        // Move left
        for (int j = dloc; j >= 0; j--)
        {
            printf("%d", queue[j]);
            if (j != 0)
                printf(" --> ");
        }
        // Then go right
        for (int j = dloc + 1; j < q_size; j++)
        {
            printf(" --> %d", queue[j]);
        }
        sum = head - LOW + (queue[q_size - 1] - LOW);
    }
    else
    {
        // Move right
        for (int j = dloc; j < q_size; j++)
        {
            printf("%d", queue[j]);
            if (j != q_size - 1)
                printf(" --> ");
        }
        // Then go left
        for (int j = dloc - 1; j >= 0; j--)
        {
            printf(" --> %d", queue[j]);
        }
        sum = (HIGH - head) + (HIGH - queue[0]);
    }

    printf("\n\nTotal head movement = %d cylinders\n", sum);

    return 0;
}
