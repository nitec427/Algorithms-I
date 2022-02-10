int partition(vector<Tweet>& tws, int left, int right){
    // I use the pseudocode given in the lecture
    Tweet pivot = tws[left];
    int i = left;
    for(int j = left +1; j<=right; j++){
        if(tws[j]<pivot || pivot.is_equal(tws[j])){
            i++;
            swap(tws[i], tws[j]);
        }
    }
    swap(tws[i], tws[left]);
    return i;
}
// Initial call for the quicksort is (tws,1,n)
void det_qsort(vector<Tweet>& tws, int left, int right){
    if (left < right)
    {
        int pivot = partition(tws,left,right);
        det_qsort(tws, left, pivot-1);
        det_qsort(tws, pivot+1, right);
    }
}


void random_qsort(vector<Tweet>& tws, int left, int right){
    if (left < right)
    {
        // Provide the seed
        srand(time(NULL));
        // Select a pivot randomly
        int random = left + rand() % (right - left);
        // Then swap it with the pivot element (in my case this would be the first one)
        swap(tws[random],tws[left]);
        int pivot = partition(tws,left,right);
        random_qsort(tws, left, pivot-1);
        random_qsort(tws, pivot+1, right);
    }
}